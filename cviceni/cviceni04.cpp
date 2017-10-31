//
// Created by Jakub Trmal on 24.10.17.
//
#include <iostream>

using namespace std;

// definice typu - znovupouzitelne
typedef struct {
    double *data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
} T_vector;

// jednorazova struktura vector
struct vector {
    double* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

/*************** Array functions ***************/
void print_array(const double *array, size_t size);

void copy_array(const double *from, double *to, size_t size);

void resize_array(double*& array, size_t old_size, size_t new_size);

/*************** Vector functions ***************/
void print_vector(const T_vector &vector);

size_t size(const T_vector &vector);
size_t capacity(const T_vector &vector);
bool empty(const T_vector &vector);

// push number to my structure
void push_back(T_vector &vector, double number);

void dispose(T_vector &vector);

double& at(T_vector &vector, size_t index);
double at(const T_vector &vector, size_t index);

void pop_back(T_vector &vector);

void reserve(T_vector &vector, size_t capacity);

/*************** Array functions ***************/

void print_array(const double *array, size_t size) {
    if (size != 0 || array != nullptr) {
        for (int i = 0; i < size; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
}

void copy_array(const double *from, double *to, size_t size) {
    if (size != 0 || from != nullptr || to != nullptr) {
        for (int i = 0; i < size; ++i) {
            to[i] = from[i];
        }
    }
}

void resize_array(double*& array, size_t old_size, size_t new_size) {
    if (old_size <= 0 || new_size <= 0 || array == nullptr) {
        throw std::runtime_error("resize_array fail");
    }
    double *new_array = new double[new_size];
    if (old_size < new_size) {
        copy_array(array, new_array, old_size);
    } else {
        copy_array(array, new_array, new_size);
    }
    delete[] array;
    array = new_array;
}


/*************** Vector functions ***************/

size_t size(const T_vector &vector) {
    return vector.size;
}

size_t capacity(const T_vector &vector) {
    return vector.capacity;
}

bool empty(const T_vector &vector) {
    return vector.size==0;
}

void push_back(T_vector &vector, double number) {
    
}


/*************** Test functions ***************/

void test01() {
    const double staticArr[3] = {
            1.23, 2.34, 3.45
    };
    double *dynamicArr = new double[3]{};
    print_array(staticArr, 3);  // vypíše: 1.23 2.34 3.45
    print_array(dynamicArr, 3); // vypíše 0 0 0
    delete[] dynamicArr;
}

void test02() {
    const double staticArr[3] = {1.23, 2.34, 3.45};
    double *dynamicArr = new double[3]{};
    copy_array(staticArr, dynamicArr, 3);
    print_array(staticArr, 3);  // vypíše: 1.23 2.34 3.45
    print_array(dynamicArr, 3); // vypíše: 1.23 2.34 3.45
    delete[] dynamicArr;
}

void test03() {
    double* arr = new double[3];
    arr[0] = 1.23;
    arr[1] = 2.34;
    arr[2] = 3.45;
    resize_array(arr, 3, 5);
    arr[3] = 4.56;
    arr[4] = 5.67;
    resize_array(arr, 5, 6);
    arr[5] = 6.78;
    print_array(arr, 6); // vypíše: 1.23 2.34 3.45 4.56 5.67 6.78
    delete[] arr;
}

int main(int argc, char **argv) {
    clock_t start = clock();

//    test01();
//    test02();
    test03();

    std::vector
    clock_t  end = clock();
    cout<<endl<<"Runtime: "<<(end-start)<<" ms"<<endl;
    return 0;
}