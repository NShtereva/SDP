#include <iostream>

const unsigned N = 3;
const unsigned M = 4;
const unsigned P = 5;

void matrixMult(const int matrix1[][M], const int matrix2[][P])
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            std::cout << matrix1[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < P; j++)
        {
            std::cout << matrix2[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    int result[N][P];
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < P; j++)
        {
            result[i][j] = 0;
            for(int k = 0; k < M; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < P; j++)
        {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int matrix1[N][M] = { 1,  2,  3,  4,
                          5,  6,  7,  8,
                          9, 10, 11, 12 };

    int matrix2[M][P] = { -3,  2, 3, 4, 0,
                           5,  0, 7, 1, 0,
                           7, -5, 0, 0, 1,
                           2,  1, 0, 1, 3 };

    matrixMult(matrix1, matrix2);
    return 0;
}
