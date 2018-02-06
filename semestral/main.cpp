#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>

#include "printer.hpp"
#include "graph.hpp"

std::mutex mtx;

class blocking_bounded_queue {
public:
    explicit blocking_bounded_queue(std::size_t size = 10) : size_limit{size}, closing{false} {}

    bool add(int e) {
        std::unique_lock<std::mutex> lg(mutex);
        add_variable.wait(reinterpret_cast<unique_lock<__1::mutex> &>(lg),
                          [&]() -> bool { return queue.size() < size_limit || closing; });
        if (closing) {
            return false;
        }
        queue.push(e);
        take_variable.notify_one();
        return true;
    }

    bool take(int &out) {
        std::unique_lock<std::mutex> lg(mutex);
        take_variable.wait(reinterpret_cast<unique_lock<__1::mutex> &>(lg),
                           [&]() -> bool { return !queue.empty() || closing; });
        if (queue.empty()) {
            return false;
        }
        out = queue.front();
        queue.pop();
        add_variable.notify_one();
        return true;
    }

    void close() {
        std::unique_lock<std::mutex> lg(mutex);
        closing = true;
        add_variable.notify_all();
        take_variable.notify_all();
    }

    ~blocking_bounded_queue() {
        close();
    }

private:
    std::queue<int> queue;
    std::size_t size_limit;
    std::mutex mutex;
    std::condition_variable take_variable, add_variable;
    bool closing;
};

template<typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

//    cout << "[DEBUG] arc: " << argc - 1 << endl;
//    cout << "[DEBUG] argument: " << argv[0] << endl;
//    cout << "[DEBUG] arg: " << argv[1] << endl;

    if (argc == 1) {
        no_args();

        // single argument
    } else if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            help();
        } else if (strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "--version") == 0) {
            version();
        } else {
            try {
                graph graph(argv[1]);

                int result[graph.get_nodes()];

                for (int i = 0; i < graph.get_nodes(); ++i) {
                    graph.dijkstra(i, result);
                    graph.print_solution(mtx, i, result);
                }
            } catch (std::runtime_error &e) {
                cout << e.what() << endl;
            }
        }

        // multi thread
    } else if (argc == 3) {

        if (strcmp(argv[2], "-t") == 0) {
            try {
                graph graph(argv[1]);
                unsigned int num_threads = std::thread::hardware_concurrency();

                blocking_bounded_queue bbq;
                auto prod = [&]() {
                    for (int i = 0; i < graph.get_nodes(); ++i) {
                        bbq.add(i);
                    }
                    bbq.close();
                };

                auto cons = [&]() {
                    int out;
                    int result[graph.get_nodes()];

                    while (bbq.take(out)) {
                        graph.dijkstra(out, result);
                        graph.print_solution(mtx, out, result);
                    }
                };

                std::thread t1(prod);

                vector<thread> workers;
                for (unsigned int i = 0; i < num_threads; ++i) {
                    workers.emplace_back(cons);
                    workers[i].join();
                }

                t1.join();
            } catch (std::runtime_error &e) {
                cout << e.what() << endl;
            }

        } else {
            unknown_arg();
        }
    } else {
        too_many_args();
        help();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\nRuntime: " << to_ms(end - start).count() << " ms\n";
    return 0;
}
