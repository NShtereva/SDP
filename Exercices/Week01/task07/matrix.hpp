#ifndef __MATRIX_HPP
#define __MATRIX_HPP

#include <cassert>

template <typename T>
class Matrix
{
    private:
        static const std::size_t N = 3;
        T matrix[N][N];

    public:
        Matrix();

        void read();
        void print() const;

        Matrix& operator += (const Matrix& other);
        Matrix& operator *= (const Matrix& other);

        T* operator [] (int i);
};

template <typename T>
Matrix<T>::Matrix()
{ 
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
}

template <typename T>
void Matrix<T>::read()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            std::cin >> this->matrix[i][j];
        }
    }
}

template <typename T>
void Matrix<T>::print() const
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            std::cout << this->matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator += (const Matrix<T>& other)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            this->matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
        }
    }

    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator *= (const Matrix<T>& other)
{
    T result[N][N];
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            result[i][j] = 0;
            for(int k = 0; k < N; k++)
            {
                result[i][j] += this->matrix[i][k] * other.matrix[k][j];
            }
        }
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            this->matrix[i][j] = result[i][j];
        }
    }

    return *this;
}

template <typename T>
T* Matrix<T>::operator [] (int i)
{
    assert(i >= 0 && i < N);
    return reinterpret_cast<T*>(&this->matrix[i]);
}

#endif
