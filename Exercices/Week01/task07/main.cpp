#include <iostream>

#include "matrix.hpp"

int main()
{
    Matrix<int> matrix1;
    Matrix<int> matrix2;

    std::cout << "matrix1:" << std::endl;
    matrix1.read();

    std::cout << std::endl;
    std::cout << "matrix2:" << std::endl;
    matrix2.read();

    std::cout << std::endl;
    matrix1 += matrix2;

    std::cout << "matrix1 += matrix2" << std::endl;
    matrix1.print();

    std::cout << std::endl;
    matrix1 *= matrix2;

    std::cout << "matrix1 *= matrix2" << std::endl;
    matrix1.print();

    std::cout << std::endl
              << "matrix1[2][1] = "
              << matrix1[2][1] 
              << std::endl;
    return 0;
}

/*
matrix1:
1 2 3
0 1 3
1 1 1

matrix2:
1 0 1
0 1 1
1 2 3

matrix1 += matrix2
2 2 4
0 2 4
2 3 4

matrix1 *= matrix2
6 10 16
4 10 14
6 11 17

matrix1[2][1] = 11
*/
