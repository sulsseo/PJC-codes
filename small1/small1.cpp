#include <iostream>
#include <sstream>
#include <iomanip>
#include "small1.hpp"

using namespace std;

/*
 * DONE
 */
std::pair<int, int> parse_matrix(std::istream &in) {
    string line;
    string number;
    int cols = 0;
    int rows = 0;

    while (getline(in, line)) {
        stringstream sstream(line);
        rows++;

        std::vector<std::string> storage;

        while (sstream >> number) {
            storage.push_back(number);
        }

        if (cols == 0)
            cols = storage.size();

        else if (cols != storage.size())
            throw std::invalid_argument("number of columns is not consistent!");
    }

    return {rows, cols};
}

void print_hline(std::ostream &out, int length) {
    for (int j = 0; j < length; ++j) {
        out << "-";
    }
    out << endl;
}

/*
 * DONE
 */
void print_table(std::ostream &out, const std::vector<std::string> &vec) {
    std::vector<std::string> container_1, container_2;
    size_t gap = 0;

    for (int i = 0; i < vec.size(); ++i) {
        std::string element = vec.at(i);
        size_t el_size = element.size();

        // container 2
        if (i % 2) container_2.push_back(element);

        // container 1
        else container_1.push_back(element);

        // set gap
        if (el_size > gap) gap = el_size;
    }

    size_t length = 2 * gap + 5;

    print_hline(out, length);

    for (int k = 0; k < container_1.size(); ++k) {
        out << "| " << std::setw(gap) << container_1.at(k) << "| ";

        if (k + 1 > container_2.size()) {
            out << std::setw(gap) << " ";
        } else {
            out << std::setw(gap) << container_2.at(k);
        }
        out << "|" << std::endl;
    }

    print_hline(out, length);
}

/*
 * octal number detect
 *
 * return true and int value if number is octal
 * return false otherwise
 */
bool is_oct(std::string number, int &value) {
    stringstream ss(number);
    ss >> oct >> value;
    if (value == 0) {
        return number == "0";
    }
    return !ss.good();
}

/*
 * decimal number detect
 *
 * return true and int value if number is decimal
 * return false otherwise
 */
bool is_dec(std::string number, int &value) {
    stringstream ss(number);
    ss >> dec >> value;
    return !ss.good();
}

/*
 * hexa number detect
 *
 * return true and int value if number is hexa
 * return false otherwise
 */
bool is_hex(std::string number, int &value) {
    stringstream ss(number);
    ss >> hex >> value;
    if (value == 0) {
        return number == "0";
    }
    return !ss.good();
}

/*
 * DONE
 */
bool validate_line(const std::string &str) {
    if (str.size() == 0) return false; // no input

    std::stringstream ss(str);
    std::vector<string> data(4); // raw data

    ss >> data.at(0); // bool

    if (!ss.good()) return false; // empty stream
    ss >> data.at(1); // oct

    if (!ss.good()) return false;
    ss >> data.at(2); // dec

    if (!ss.good()) return false;
    ss >> data.at(3); // hex

    // values of data
    std::vector<int> values(3);

    if (is_oct(data.at(1), values.at(0))) {
        if (is_dec(data.at(2), values.at(1))) {
            if (is_hex(data.at(3), values.at(2))) {
                if (data.at(0) == "true") {
                    return values.at(0) == values.at(1) && values.at(0) == values.at(2);
                } else if (data.at(0) == "false") {
                    return values.at(0) != values.at(1) ||
                           values.at(1) != values.at(2) ||
                           values.at(0) != values.at(2);
                } else return false;
            } else return false;
        } else return false;
    } else return false;
}

/*
 * find max between two given vectors<int> and save it to max
 */
void find_max(std::vector<int> &max, std::vector<int> &number) {
    // if one is longer than other result is clear
    if (max.size() < number.size()) {
        max = number;
    } else if (max.size() == number.size()) {
        for (int i = 0; i < max.size(); ++i) {
            if (max.at(i) < number.at(i)) {
                max = number;
                break;
            }
        }
    }
}

/**
 * return vector as string
 *
 * @param to_string
 * @return
 */
std::string vec_to_str(std::vector<int> to_string) {
    stringstream ss;
    for (int i = 0; i < to_string.size(); ++i) {
        ss<<to_string.at(i);
    }
    return ss.str();
}

/*
 * DONE
 */
std::string max_number(std::istream &in) {
    std::vector<int> max;
    std::vector<int> readed;

    char token;

    while (in.get(token)) {
        if (token == ',') {
            // end of number
            find_max(max, readed);
            readed.clear();
        } else {
            readed.push_back(token - 48);
        }
    }

    find_max(max, readed);

    return vec_to_str(max);
}
