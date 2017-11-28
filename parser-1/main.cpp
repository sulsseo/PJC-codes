//
// Created by Jakub Trmal on 25.11.17.
//

#include <stdio.h>
#include <memory>
#include <sstream>
#include <iostream>
#include "expr.hpp"


using namespace std;

bool is_num(const std::string token) {
    bool dot = false;
    for (char c : token) {
        if (c == '.') {
            if (!dot) dot = true;
            else return false;
        } else if (!isdigit(c)) return false;
    }
    return true;
}

int main() {
//    auto e = create_expression_tree("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
    auto e1 = create_expression_tree("2^3^3");
//    auto e2 = create_expression_tree("(22.13)+1"); //TODO: double expression
//    string s = "(22.13)+1";
    e1->evaluate();
}