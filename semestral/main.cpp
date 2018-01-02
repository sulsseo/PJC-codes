#include <iostream>

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();



    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\nRuntime: " << to_ms(end - start).count() << " ms\n";
    return 0;
}