//
// Created by Jakub Trmal on 25.11.17.
//

#include <stdio.h>
#include <memory>
#include <sstream>
#include "expr.hpp"


using namespace std;

int main() {
    auto e = create_expression_tree("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
    auto e1 = create_expression_tree("2^3^3");
    auto e2 = create_expression_tree("(22.13)+1"); //TODO: double expression

}