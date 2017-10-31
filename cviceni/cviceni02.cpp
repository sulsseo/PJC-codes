#include <iostream>
#include <iomanip>

using namespace std;

void example01() {
    cout << "write your name:" << endl;
    string jmeno;
    getline(cin, jmeno);
    cout << "your name: " << jmeno << endl;
}

/**
 * funkce, ktera osetruje, aby vstup byl takovy jaky chci
 * v pripadech kdy je neco v neporadku, tak se vraci a znovu ceka
 *
 * @return precteny double
 */
double readDouble() {
    double d;
    std::cin >> d;

    if (std::cin.good()) {
        return d;
    }
    else if (std::cin.bad() || std::cin.eof()) {
        throw std::runtime_error("readDouble() failed");
    }
    else {
        std::cin.clear();
        std::cin.ignore(1, '\n');
        return readDouble();
    }
}

void hline(int W) {
    for (int i = 0; i < W; ++i) {
        std::cout << '-';
    }
    std::cout << '\n';
}

void formattedOutput() {
    const int W = 8;

    hline(W);                                    // --------
    std::cout << std::setw(W) << 1234 << '\n';   //     1234
    std::cout << std::setw(W) << 1.2 << '\n';    //      1.2
    std::cout << std::setw(W) << 1.2e10 << '\n'; //  1.2e+10
    std::cout << std::setw(W) << "abcd" << '\n'; //     abcd
    hline(W);                                    // --------
    std::cout << std::hex;
    std::cout << std::setw(W) << 255 << '\n';    //       ff
    std::cout << std::showbase;
    std::cout << std::setw(W) << 255 << '\n';    //     0xff
    std::cout << std::dec;
    std::cout << std::setw(W) << 255 << '\n';    //      255
    hline(W);                                    // --------
}

int main() {
//    run readDouble
//    double a = readDouble();
//    cout << a << endl;


    return 0;
}