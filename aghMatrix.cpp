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
void aghMatrix<T>::setItem(const int row, const int col, const T &value) {
    bool rowInRange = (row > 0) && (row < this->rows);
    bool colInRange = (col > 0) && (col < this->cols);
    if (!rowInRange || !colInRange) throw aghException(0, "Index out of range", __FILE__, __LINE__);
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
}

template<class T>
aghMatrix aghMatrix<T>::operator+(const aghMatrix &matrix) {

}

template<class T>
aghMatrix aghMatrix<T>::operator-(const aghMatrix &matrix) {

}

template<class T>
aghMatrix aghMatrix<T>::operator*(const aghMatrix &matrix) {

}

template<class T>
bool aghMatrix<T>::operator==(const aghMatrix &matrix) {

}

template<class T>
bool aghMatrix<T>::operator!=(const aghMatrix &matrix) {

}

template<class T>
aghMatrix& aghMatrix<T>::operator=(const aghMatrix &matrix) {

}
