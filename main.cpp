#include <iostream>
#include "memcheck.h"
using namespace std;

class A{};

int main() {
    A *p = new A();
    A *p2 = new A();
    int  *arr = new int[100];
    char *arr2 = new char[512];

    delete p;
    // delete p2;
    delete arr;
    // delete arr2;

    return 0;
}