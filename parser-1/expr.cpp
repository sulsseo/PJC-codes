#include <sstream>
#include <queue>
#include <stack>
#include <iostream>
#include "expr.hpp"

using namespace std;

struct operation {
    char sign;
    int priority;
    char assiociativity;
};


std::ostream &operator<<(std::ostream &out, const expr &e) {
    out << "a";
    return out;
}

int get_priority(const char c) {
    if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '^') return 3;
    else return -1;
}

char get_associativity(const char c) {
    if (c == '^') return 'R';
    else return 'L';
}


//TODO: double expression
/**
 * shunting yard algorithm to convert expressions from infix to postfix
 *
 *  Priorities
 *
 *  ^       3   R
 *  *, /    2   L
 *  +, -    1   L
 *
 * @param infix
 * @return
 */
std::stringstream shunting_yard(const std::string &infix) {
    string token;
    stringstream sout;
    stringstream sin(infix);
    stack<operation> operators;

    while (sin.good()) {
        sin >> token;
        if (isdigit(token[0])) {
            sout << token;
        } else if (token[0] == '(') {
            operators.push({token[0], get_priority(token[0]), get_associativity(token[0])});

        } else if (token[0] == ')') {
            while (operators.top().sign != '(') {
                sout << operators.top().sign;
                operators.pop();
            }
            operators.pop();
        } else {
            operation o = {token[0], get_priority(token[0]), get_associativity(token[0])};
            while (!operators.empty() && (o.assiociativity == 'L' && operators.top().priority >= o.priority)) {
                sout << operators.top().sign;
                operators.pop();
            }
            operators.push(o);
        }
    }

    while (!operators.empty()) {
        sout << operators.top().sign;
        operators.pop();
    }

    return sout;
}

std::unique_ptr<expr> create_expression_tree(const std::string &expression) {
//    stack<
    stringstream s = shunting_yard(expression);
    cout << s.str() << endl;
    return {};
}

