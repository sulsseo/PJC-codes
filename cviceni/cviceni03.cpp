//
// Created by Jakub Trmal on 17.10.17.
//

#include <string>
#include <iostream>
#include <vector>

using namespace std;

void example01() {
    std::vector<std::string> jmena = {"Petr", "Jan", "Jana", "Karel", "Katka"};

    for (const auto& s : jmena) {
        std::cout << s << '\n';
    }
}

int main() {

    std::string test = "1 2 3 4";
    cout << test << endl;
}