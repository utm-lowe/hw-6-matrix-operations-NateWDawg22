#include "matrix.h"
#include <iomanip>

// Constructor
Matrix::Matrix(unsigned int rows, unsigned int cols)
    : ar(nullptr), m(0), n(0)
{
    m = rows;
    n = cols;
    ar = new double*[m];
    for (int i = 0; i < m; ++i) {
        ar[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            ar[i][j] = 0.0;
        }
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& rhs)
    : ar(nullptr), m(rhs.m), n(rhs.n)
{
    ar = new double*[m];
    for (int i = 0; i < m; ++i) {
        ar[i] = new double[n];
        for (int j = 0; j < n; ++j) {
            ar[i][j] = rhs.ar[i][j];
        }
    }
}

// Destructor
Matrix::~Matrix()
{
    if (ar) {
        for (int i = 0; i < m; ++i) {
            delete [] ar[i];
        }
        delete [] ar;
        ar = nullptr;
    }
}

int Matrix::getRows() const { return m; }
int Matrix::getCols() const { return n; }

double& Matrix::at(unsigned int row, unsigned int col)
{
    return ar[row][col];
}

const double& Matrix::at(unsigned int row, unsigned int col) const
{
    return ar[row][col];
}

Matrix& Matrix::operator=(const Matrix& rhs)
{
    if (this == &rhs) return *this;

    // If dimensions differ, reallocate
    if (m != rhs.m || n != rhs.n) {
        if (ar) {
            for (int i = 0; i < m; ++i) delete [] ar[i];
            delete [] ar;
        }
        m = rhs.m;
        n = rhs.n;
        ar = new double*[m];
        for (int i = 0; i < m; ++i) ar[i] = new double[n];
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            ar[i][j] = rhs.ar[i][j];
        }
    }

    return *this;
}

// Matrix arithmetic operators
Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    Matrix result(m1.getRows(), m1.getCols());
    for (int i = 0; i < m1.getRows(); ++i)
        for (int j = 0; j < m1.getCols(); ++j)
            result.at(i,j) = m1.at(i,j) + m2.at(i,j);
    return result;
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    Matrix result(m1.getRows(), m1.getCols());
    for (int i = 0; i < m1.getRows(); ++i)
        for (int j = 0; j < m1.getCols(); ++j)
            result.at(i,j) = m1.at(i,j) - m2.at(i,j);
    return result;
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    Matrix result(m1.getRows(), m2.getCols());
    for (int i = 0; i < m1.getRows(); ++i) {
        for (int j = 0; j < m2.getCols(); ++j) {
            double sum = 0.0;
            for (int k = 0; k < m1.getCols(); ++k) {
                sum += m1.at(i,k) * m2.at(k,j);
            }
            result.at(i,j) = sum;
        }
    }
    return result;
}

Matrix operator*(double scalar, const Matrix& m)
{
    Matrix result(m.getRows(), m.getCols());
    for (int i = 0; i < m.getRows(); ++i)
        for (int j = 0; j < m.getCols(); ++j)
            result.at(i,j) = scalar * m.at(i,j);
    return result;
}

Matrix operator*(const Matrix& m, double scalar)
{
    return scalar * m;
}

// Output operator: prints each element with field width 10 and a trailing space
std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.getRows(); ++i) {
        for (int j = 0; j < m.getCols(); ++j) {
            os << std::setw(10) << m.at(i,j) << " ";
        }
        // print newline after each row except the last; caller may add one
        if (i < m.getRows() - 1)
            os << std::endl;
    }
    return os;
}

// Input operator: reads values into an existing matrix
std::istream& operator>>(std::istream& is, Matrix& m)
{
    for (int i = 0; i < m.getRows(); ++i)
        for (int j = 0; j < m.getCols(); ++j)
            is >> m.at(i,j);
    return is;
}
