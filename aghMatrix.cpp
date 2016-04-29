#include "aghMatrix.h"

template<class T>
aghMatrix<T>::aghMatrix() : matrixPtr(nullptr) {
    this->createMatrix(10, 10);
}

template<class T>
aghMatrix<T>::aghMatrix(int rows, int cols) : matrixPtr(nullptr) {
    this->createMatrix(rows, cols);
}

template<class T>
aghMatrix<T>::~aghMatrix() {
    for (int i = 0; i < this->rows; i++)
        delete[] matrixPtr[i];
    delete[] matrixPtr;
}

template<class T>
void aghMatrix<T>::createMatrix(const int rows, const int cols) {
    this->matrixPtr = new T *[rows];
    for (int i = 0; i < rows; i++)
        this->matrixPtr[i] = new T[cols];
    this->rows = rows;
    this->cols = cols;
}

template<class T>
bool aghMatrix<T>::checkRowCol(const int row, const int col) const {
    bool rowInRange = (row > 0) && (row < this->rows);
    bool colInRange = (col > 0) && (col < this->cols);
    if (!rowInRange || !colInRange) return true;
    return false;
}

template<class T>
int aghMatrix<T>::getRows() const {
    return this->rows;
}

template<class T>
int aghMatrix<t>::getCols() const {
    return this->cols;
}

template<class T>
T aghMatrix<T>::getItem(const int row, const int col) const {
    if (this->checkRowCol(row, col))
        throw aghException(0, "Index out of range", __FILE__, __LINE__);
    return this->matrixPtr[row][col];
}

template<class T>
void aghMatrix<T>::setItem(const int row, const int col, const T &value) {
    if (this->checkRowCol(row, col))
        throw aghException(0, "Index out of range", __FILE__, __LINE__);
    this->matrixPtr[row][col] = value;
    return;
}

template<class T>
void aghMatrix<T>::setItems(const T *values) {
    int elem = 0;
    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j) {
            this->matrixPtr[i][j] = values[elem];
            elem++;
        }

    return;
}

template<class T>
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

template<class T>
aghMatrix aghMatrix<T>::add(const aghMatrix &matrix) const {
    bool equalRows = this->rows == matrix.getRows();
    bool equalCols = this->cols == matrix.getCols();
    if (!equalRows || !equalCols)
        throw aghException(1, "Tried to add matrices with wrong dimensions!", __FILE__, __LINE__);

    aghMatrix <T>newMatrix(this->rows, this->cols);

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j)
            newMatrix.setItem(i, j, this->matrixPtr[i][j] + matrix->getItem(i, j));

    return newMatrix;
}

template<>
aghMatrix aghMatrix<const char>::add(const aghMatrix &matrix) const {
    bool equalRows = this->rows == matrix.getRows();
    bool equalCols = this->cols == matrix.getCols();
    if (!equalRows || !equalCols)
        throw aghException(1, "Tried to add matrices with wrong dimensions!", __FILE__, __LINE__);

    aghMatrix <int>newMatrix(this->rows, this->cols);

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j)
            newMatrix.setItem(i, j, int(this->matrixPtr[i][j]) - 97 + int(matrix->getItem(i, j)) - 97);

    return newMatrix;
}

template<class T>
aghMatrix aghMatrix<T>::multiply(const aghMatrix &matrix) const {
    bool equalDimensions = this->cols == matrix.getRows();
    if (!equalDimensions)
        throw aghException(1, "Tried to multiply matrices with wrong dimensions!", __FILE__, __LINE__);

    aghMatrix <T>newMatrix(this->rows, matrix.getCols());

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < matrix.getCols(); ++j)
            for (int k = 0; k < this->cols; ++k) {
                T newValue = newMatrix.getItem(i, j) + this->matrixPtr[i, k] * matrix.getItem(k, j);
                newMatrix.setItem(i, j, newValue);
            }

    return newMatrix;
}

template<class T>
bool aghMatrix<T>::equal(const aghMatrix &matrix) const {
    if (this->checkRowCol(matrix.getRows(), matrix.getCols()))
        return false;

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j)
            if (this->matrixPtr[i][j] != matrix.getItem(i, j))
                return false;

    return true;
}

template<class T>
aghMatrix& aghMatrix::overwrite(const aghMatrix &matrix) {
    if (this->checkRowCol(matrix.getRows(), matrix.getCols()))
        throw aghException(1, "You tried to overwrite matrix using matrix with wrong dimensions", __FILE__, __LINE__);

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j)
            this->matrixPtr[i][j] = matrix.getItem(i, j);

    return *this;
}

template<class T>
aghMatrix aghMatrix<T>::operator+(const aghMatrix &matrix) const {
    return this->add(matrix);
}

template<class T>
aghMatrix aghMatrix<T>::operator*(const aghMatrix &matrix) const {
    return this->multiply(matrix);
}

template<class T>
bool aghMatrix<T>::operator==(const aghMatrix &matrix) const {
    return this->equal(matrix);
}

template<class T>
bool aghMatrix<T>::operator!=(const aghMatrix &matrix) const {
    return !(this->equal(matrix));
}

template<class T>
aghMatrix& aghMatrix<T>::operator=(const aghMatrix &matrix) {
    return this->overwrite(matrix);
}

template<class T>
T aghMatrix<T>::operator()(const int row, const int col) {
    return this->getItem(row, col);
}
