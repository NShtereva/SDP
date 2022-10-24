#include <iostream>

const unsigned N = 3;
const unsigned M = 4;

void printMatrix(const int matrix[][M])
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void addMatrices(const int matrix1[][M], const int matrix2[][M])
{
    printMatrix(matrix1);
    printMatrix(matrix2);

    int result[N][M];
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    printMatrix(result);
}

int main()
{
    int matrix1[N][M] = { 1,  2,  3,  4,
                          5,  6,  7,  8,
                          9, 10, 11, 12 };

    int matrix2[N][M] = { -3,   2,  3,  4,
                           5,  15,  7,  8,
                           7,  -5,  0, -9 };

    addMatrices(matrix1, matrix2);
    return 0;
}
