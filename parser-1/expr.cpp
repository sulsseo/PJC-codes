#include <sstream>
#include <queue>
#include <stack>
#include <iostream>
#include <cmath>
#include "expr.hpp"

using namespace std;

struct operation {
    char sign;
    int priority;
    char assiociativity;
};

/************** Tree classes *******************/


class result : public expr {
private:
    double value;

    friend std::ostream &operator<<(std::ostream &out, const result &r) {
        out << "result: " << endl;
        return out;
    }

public:
    result(double a) : value(a) {}

    ~result() = default;

    double evaluate() {
        return value;
    }
};

/************** END Tree classes *******************/


bool is_number(const std::string token) {
    bool dot = false;
    for (char c : token) {
        if (c == '.') {
            if (!dot) dot = true;
            else return false;
        } else if (!isdigit(c)) return false;
    }
    return true;
}

// get priority for operation
int get_priority(const char c) {
    if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '^') return 3;
    else return -1;
}

// get associativity for operation
char get_associativity(const char c) {
    if (c == '^') return 'R';
    else return 'L';
}

std::string make_clear(const std::string data) {
    stringstream sin(data);
    stringstream sout;

    int token;
    bool number = false;

    while ((token = sin.get()) != -1) {
        if (!isdigit(token) && token != 46 && number) {
            sout << ";";
            number = false;
        }
        if (isdigit(token) || token == 46) {
            sout << (char) token;
            if (!number) number = true;
        } else if (isspace(token)) {
            continue;
        } else if (token == 40 || token == 41) {
            // brackets
            sout << (char) token << ";";

        } else if (token == 42 || // *
                   token == 43 || // +
                   token == 45 || // -
                   token == 47 || // /
                   token == 94)   // ^
        {
            sout << (char) token << ";";
        } else {
            cout << "not processed: " << (char) token << endl;
        }
    }
    sout << ";";
    return sout.str();
}

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
std::stringstream shunting_yard(const std::string infix) {
    string token;
    string clear_infix = make_clear(infix);
    stringstream sout;
    stringstream sin(clear_infix);
    stack<operation> operators;

    // todo: learn to split only by whitespace

    while (getline(sin, token, ';')) {
        if (is_number(token)) {
            sout << token << ";";
        } else if (token[0] == '(') {
            operators.push({token[0], get_priority(token[0]), get_associativity(token[0])});

        } else if (token[0] == ')') {
            while (operators.top().sign != '(') {
                sout << operators.top().sign << ";";
                operators.pop();
            }
            operators.pop();
        } else {
            operation o = {token[0], get_priority(token[0]), get_associativity(token[0])};
            while (!operators.empty() && (o.assiociativity == 'L' && operators.top().priority >= o.priority)) {
                sout << operators.top().sign << ";";
                operators.pop();
            }
            operators.push(o);
        }
    }

    while (!operators.empty()) {
        sout << operators.top().sign << ";";
        operators.pop();
    }

    return sout;
}

std::unique_ptr<expr> create_expression_tree(const std::string &expression) {
    stack<double> stack;
    string token;
    stringstream data = shunting_yard(expression);

    int counter = 0;
    while (getline(data, token, ';')) {
        if (is_number(token)) {
            stack.push(stod(token));
        } else {
            double num1, num2;
            switch (token[0]) {
                case '+':
                    num1 = stack.top();
                    stack.pop();
                    num2 = stack.top();
                    stack.pop();
                    stack.push(num1 + num2);
                    break;
                case '-':
                    num1 = stack.top();
                    stack.pop();
                    num2 = stack.top();
                    stack.pop();
                    stack.push(num1 - num2);
                    break;
                case '/':
                    num1 = stack.top();
                    stack.pop();
                    num2 = stack.top();
                    stack.pop();
                    try {
                        stack.push(num1 / num2);
                    } catch (exception &e) {
                        // zero division
                        cout << e.what() << endl;
                    }
                    break;
                case '*':
                    num1 = stack.top();
                    stack.pop();
                    num2 = stack.top();
                    stack.pop();
                    stack.push(num1 * num2);
                    break;
                case '^':
                    num1 = stack.top();
                    stack.pop();
                    num2 = stack.top();
                    stack.pop();
                    stack.push(pow(num1, num2));
                    break;
                default:
                    cout << "unknown token: " << token << endl;
                    break;
            }
        }
    }
    std::unique_ptr<expr> ptr = std::make_unique<result>(result(stack.top()));
    return ptr;

}

std::ostream &operator<<(std::ostream &out, const expr &e) {
    return out << e.evaluate();
}
