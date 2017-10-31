//
// Created by Jakub Trmal on 17.10.17.
//

#include<iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

/*
 *  CHECK( !validate_line("false 07 7 G") )  >  false
 *  CHECK( !validate_line("false 88 88 0x58") )  >  false
 */

std::string vec_to_str(std::vector<string> to_string) {
    stringstream ss;
    for (int i = 0; i < to_string.size(); ++i) {
        ss<<to_string.at(i);
    }
    return ss.str();
}

bool is_oct(std::string number) {
    stringstream ss(number);
    int value;
    ss >> oct >> value;

    return !ss.good();
}

bool is_hex(std::string number) {
    stringstream ss(number);
    int value;
    ss >> hex >> value;
    return !ss.good();
}

int main() {
    string given = "fase 07 7 G";
    stringstream ss(given);
    vector<string> data(4);

    if (given.size()==0) return -1;

    ss >> data.at(0); // bool

    if (!ss.good()) return -1; // empty stream
    ss >> data.at(1); // oct

    if (!ss.good()) return -1;
    ss >> data.at(2); // dec

    if (!ss.good()) return -1;
    ss >> data.at(3); // hex

    cout << "je oct? " << is_oct(data.at(1)) << endl;
    cout << "je hex? " << is_hex(data.at(3)) << endl;

}