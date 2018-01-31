#include <iostream>
#include <thread>

#include "printer.hpp"
#include "graph.hpp"


template<typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

void thread_job(graph graph) {
    cout << "[DEBUG] thread working.." << endl;
    // TODO thread job define
}

void example02(graph graph) {
    int result[graph.get_nodes()];

    for (int i = 0; i< graph.get_nodes(); ++i) {
        graph.dijkstra(i, result);
        graph.print_solution(result);
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    cout << "[DEBUG] pocet argumentu: " << argc - 1 << endl;
    cout << "[DEBUG] argument: " << argv[0] << endl;
    cout << "[DEBUG] argument: " << argv[1] << endl;

    if (argc == 1) {
        no_args();

        // single argument
    } else if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            help();
        } else if (strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "--version") == 0) {
            version();
        } else {
            graph graph(argv[1]);
            example02(graph);
        }

        // multi thread
    } else if (argc == 3) {

        if (strcmp(argv[2], "-t") == 0) {
            unsigned int num_threads = std::thread::hardware_concurrency();
            cout << "[DEBUG] number of threads to use: " << num_threads << endl;

            graph graph(argv[1]);
//            thread_job(graph);
//            std::thread t1;
            // TODO job to thread

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
