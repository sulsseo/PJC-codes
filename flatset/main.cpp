//
// Created by Jakub Trmal on 07/12/2017.
//

#include <iostream>
#include <set>
#include <vector>
#include "flatset.h"

using namespace std;

//template <typename A, typename B, typename U = std::less<int>>
//bool f(A a, B b, U u = U())
//{
//    return u(a, b);
//}

//template <typename A, typename B>
//bool f(A a, B b, )
//{
//    return std::less<A>(a, b);
//}

void test() {
    int myints[]= {10,20,90,40,50, 30};
    std::set<int> my_set (myints,myints+5);
    std::set<int>::const_iterator it;

    my_set.insert(10);
    for (it = my_set.begin(); it != my_set.end(); ++it) {
        cout << "el:  " << it.operator*() << endl;
    }
}

int main() {

    int field[] = {1, 3, 5, 8, 4};
    flat_set<int> set(field, field+5);
    
}