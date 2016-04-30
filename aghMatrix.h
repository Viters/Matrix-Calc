#ifndef AGH_MATRIX
#define AGH_MATRIX

#include "aghException.h"
#include <iostream>
#include <cstdarg>
#include "combineCollections.h"

using namespace std;

template<typename T>
class aghMatrix {
public:
    aghMatrix();

    aghMatrix(const int rows, const int cols);

    ~aghMatrix();

    int getRows() const;

    int getCols() const;

    T getItem(const int row, const int col) const;

    void setItem(const int row, const int col, const T &value);

    void setItems(const T * value);

    void setItems(const int rows, const int cols, ...);

    aghMatrix add(const aghMatrix &matrix) const;

    aghMatrix multiply(const aghMatrix &matrix) const;

    bool equal(const aghMatrix &matrix) const;

    aghMatrix& overwrite(const aghMatrix &matrix);

    aghMatrix operator+(const aghMatrix &matrix) const;

    aghMatrix operator*(const aghMatrix &matrix) const;

    template<typename Y>
    friend bool operator==(const aghMatrix<Y> &matrix1, const aghMatrix<Y> &matrix2);

    template<typename Y>
    friend bool operator!=(const aghMatrix<Y> &matrix1, const aghMatrix<Y> &matrix2);

    aghMatrix& operator=(const aghMatrix &matrix);

    T operator()(const int row, const int col);

private:
    T **matrixPtr;
    int rows;
    int cols;

    void createMatrix(const int row, const int col);

    bool checkRowCol(const int row, const int col) const;
};

template<typename T>
aghMatrix<T>::aghMatrix() : matrixPtr(nullptr) {
    this->createMatrix(10, 10);
}

template<typename T>
aghMatrix<T>::aghMatrix(int rows, int cols) : matrixPtr(nullptr) {
    this->createMatrix(rows, cols);
}

template<typename T>
aghMatrix<T>::~aghMatrix() {
    for (int i = 0; i < this->rows; i++)
        delete[] matrixPtr[i];
    delete[] matrixPtr;
}

template<typename T>
void aghMatrix<T>::createMatrix(const int rows, const int cols) {
    this->matrixPtr = new T *[rows];
    for (int i = 0; i < rows; i++)
        this->matrixPtr[i] = new T[cols];
    this->rows = rows;
    this->cols = cols;
}

template<typename T>
bool aghMatrix<T>::checkRowCol(const int row, const int col) const {
    bool rowInRange = (row > 0) && (row < this->rows);
    bool colInRange = (col > 0) && (col < this->cols);
    if (!rowInRange || !colInRange) return true;
    return false;
}

template<typename T>
int aghMatrix<T>::getRows() const {
    return this->rows;
}

template<typename T>
int aghMatrix<T>::getCols() const {
    return this->cols;
}

template<typename T>
T aghMatrix<T>::getItem(const int row, const int col) const {
    if (this->checkRowCol(row, col))
        throw aghException(0, "Index out of range", __FILE__, __LINE__);
    return this->matrixPtr[row][col];
}

template<typename T>
void aghMatrix<T>::setItem(const int row, const int col, const T &value) {
    if (this->checkRowCol(row, col))
        throw aghException(0, "Index out of range", __FILE__, __LINE__);
    this->matrixPtr[row][col] = value;
    return;
}

template<typename T>
void aghMatrix<T>::setItems(const T *values) {
    int elem = 0;
    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j) {
            this->matrixPtr[i][j] = values[elem];
            elem++;
        }

    return;
}

template<typename T>
void aghMatrix<T>::setItems(const int rows, const int cols, ...) {
    int elemNum = rows * cols;
    if (elemNum > this->rows * this->cols)
        throw aghException(2, "Too many items for that matrix to hold", __FILE__, __LINE__);

    va_list ap;
    va_start(ap, cols);

    int elem = 0;
    for (int i = 0; i < this->rows && elem < elemNum; ++i)
        for (int j = 0; j < this->cols && elem < elemNum; ++j) {
            this->matrixPtr[i][j] = va_arg(ap, T);
            elem++;
        }

    return;
}

template<typename T>
aghMatrix<T> aghMatrix<T>::add(const aghMatrix<T> &matrix) const {
    bool equalRows = this->rows == matrix.getRows();
    bool equalCols = this->cols == matrix.getCols();
    if (!equalRows || !equalCols)
        throw aghException(1, "Tried to add matrices with wrong dimensions!", __FILE__, __LINE__);

    aghMatrix<T> newMatrix(this->rows, this->cols);

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j)
            newMatrix.setItem(i, j, this->matrixPtr[i][j] + matrix.getItem(i, j));

    return newMatrix;
}

template<typename T>
aghMatrix<T> aghMatrix<T>::multiply(const aghMatrix<T> &matrix) const {
    bool equalDimensions = this->cols == matrix.getRows();
    if (!equalDimensions)
        throw aghException(1, "Tried to multiply matrices with wrong dimensions!", __FILE__, __LINE__);

    aghMatrix<T> newMatrix(this->rows, matrix.getCols());

    T newValue;

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < matrix.getCols(); ++j)
            for (int k = 0; k < this->cols; ++k) {
                newValue = newMatrix.getItem(i, j) + this->matrixPtr[i][k] * matrix.getItem(k, j);
                newMatrix.setItem(i, j, newValue);
            }

    return newMatrix;
}

template<typename T>
bool aghMatrix<T>::equal(const aghMatrix &matrix) const {
    if (this->checkRowCol(matrix.getRows(), matrix.getCols()))
        return false;

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j)
            if (this->matrixPtr[i][j] != matrix.getItem(i, j))
                return false;

    return true;
}

template<typename T>
aghMatrix<T>& aghMatrix<T>::overwrite(const aghMatrix<T> &matrix) {
    if (this->checkRowCol(matrix.getRows(), matrix.getCols()))
        throw aghException(1, "You tried to overwrite matrix using matrix with wrong dimensions", __FILE__, __LINE__);

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j)
            this->matrixPtr[i][j] = matrix.getItem(i, j);

    return *this;
}

template<typename T>
aghMatrix<T> aghMatrix<T>::operator+(const aghMatrix<T> &matrix) const {
    return this->add(matrix);
}

template<typename T>
aghMatrix<T> aghMatrix<T>::operator*(const aghMatrix<T> &matrix) const {
    return this->multiply(matrix);
}

template<typename Y>
bool operator==(const aghMatrix<Y> &matrix1, const aghMatrix<Y> &matrix2) {
    return matrix1.equal(matrix2);
}

template<typename Y>
bool operator!=(const aghMatrix<Y> &matrix1, const aghMatrix<Y> &matrix2) {
    return !(matrix1.equal(matrix2));
}

template<typename T>
aghMatrix<T>& aghMatrix<T>::operator=(const aghMatrix<T> &matrix) {
    return this->overwrite(matrix);
}

template<typename T>
T aghMatrix<T>::operator()(const int row, const int col) {
    return this->getItem(row, col);
}




#endif
