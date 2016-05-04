#ifndef AGH_MATRIX
#define AGH_MATRIX

#include "aghException.h"
#include <iostream>
#include <tuple>
#include "stringHelper.h"

using namespace std;

/*
* \class aghMatrix
* \authors Łukasz Mielczarek, Łukasz Szcześniak
* \date
* \brief The definition of aghMatrix template class that provides interface for matrix operations
*/
template<typename T>
class aghMatrix {
public:
    /// \brief Default class constructor.
    ///        It creates matrix with 0 rows and 0 cols.
    aghMatrix();

    /// \brief Class constructor.
    ///
    /// \param rows - number of matrix rows
    /// \param cols - number of matrix columns
    aghMatrix(const int rows, const int cols);

    /// \brief Class copy constructor.
    aghMatrix(const aghMatrix<T> &matrix);

    ~aghMatrix();

    /// \brief Prints matrix to standard output.
    void print() const;

    /// \brief Returns amount of rows in matrix.
    int getRows() const;

    /// \brief Returns amount of columns in matrix.
    int getCols() const;

    /// \brief Returns specified matrix element.
    ///        Throws aghException if row or col is out of range.
    T getItem(const int row, const int col) const;

    /// \brief Sets specified matrix element.
    void setItem(const int row, const int col, const T &value);

    /// \brief Fills matrix with elements provided in array.
    ///
    /// \param const T *value - pointer to array with proper data types.
    void setItems(const T *value);

    /// \brief Fills matrix with elements provided as method arguments.
    ///
    /// \param rows - number of rows needed to hold data.
    /// \param cols - number of columns needed to hold data.
    /// \param args - (qty: rows * cols) arguments with proper data types.
    template<typename... ARGS>
    void setItems(const int rows, const int cols, ARGS... args);

    /// \brief Adds two matrices of the same type.
    ///        Throws aghException if matrices have wrong sizes.
    ///
    /// \return Result matrix.
    aghMatrix<T> add(const aghMatrix<T> &matrix) const;

    /// \brief Multiplies two matrices of the same type.
    ///        Throws aghException if matrices have wrong sizes.
    ///
    /// \return Result matrix.
    aghMatrix<T> multiply(const aghMatrix<T> &matrix) const;

    /// \brief Multiplies two matrices of the same type.
    ///        Throws aghException if matrices have wrong sizes.
    ///
    /// \return Result matrix.
    bool equal(const aghMatrix<T> &matrix) const;

    /// \brief Allows to overwrite matrix with another matrix of the same type.
    ///
    /// \return Reference to itself.
    aghMatrix<T> &overwrite(const aghMatrix<T> &matrix);

    /// \brief Overload operator + to use add() method.
    aghMatrix<T> operator+(const aghMatrix<T> &matrix) const;

    /// \brief Overload operator + to use multiply() method.
    aghMatrix<T> operator*(const aghMatrix<T> &matrix) const;

    /// \brief Overload operator == to use equal() method.
    template<typename Y>
    friend bool operator==(const aghMatrix<Y> &matrix1, const aghMatrix<Y> &matrix2);

    /// \brief Overload operator != to use negative equal() method.
    template<typename Y>
    friend bool operator!=(const aghMatrix<Y> &matrix1, const aghMatrix<Y> &matrix2);

    /// \brief Overload operator = to use overwrite() method.
    aghMatrix<T> &operator=(const aghMatrix<T> &matrix);

    /// \brief Overload operator () to use getItem() method.
    T operator()(const int row, const int col);

private:
    T **matrixPtr; /// < Stores rows array of columns array. Use as matrixPtr[row][col].
    int rows; /// < Stores amount of rows in matrix.
    int cols; /// < Stores amount of columns in matrix.

    /// \brief Creates new data structure to hold matrix elements.
    ///
    /// \param row - amount of rows needed.
    /// \param col - amount of columns needed.
    void createMatrix(const int row, const int col);

    /// \brief Checks if specified elements exists in array.
    bool isInRange(const int row, const int col) const;

    /// \brief Deallocates memory assigned to hold all matrix elements.
    void destroyMatrixPtr();
};

// --------------------------------------------------------------
// End of aghMatrix declaration
// --------------------------------------------------------------

// --------------------------------------------------------------

template<typename T>
aghMatrix<T>::aghMatrix() : matrixPtr(nullptr), rows(0), cols(0) { }

// --------------------------------------------------------------

template<typename T>
aghMatrix<T>::aghMatrix(int rows, int cols) : matrixPtr(nullptr) {
    this->createMatrix(rows, cols);
}

// --------------------------------------------------------------

template<typename T>
aghMatrix<T>::aghMatrix(const aghMatrix<T> &matrix) : matrixPtr(nullptr) {
    this->createMatrix(matrix.getRows(), matrix.getCols());
    for (int i = 0; i < matrix.getRows(); i++)
        for (int j = 0; j < matrix.getCols(); j++)
            this->matrixPtr[i][j] = matrix.getItem(i, j);
}

// --------------------------------------------------------------

template<typename T>
aghMatrix<T>::~aghMatrix() {
    if (this->matrixPtr != nullptr)
        this->destroyMatrixPtr();
    this->matrixPtr = nullptr;
    this->rows = 0;
    this->cols = 0;
}

// --------------------------------------------------------------

template<typename T>
void aghMatrix<T>::createMatrix(const int rows, const int cols) {
    this->matrixPtr = new T *[rows];
    for (int i = 0; i < rows; i++)
        this->matrixPtr[i] = new T[cols];
    this->rows = rows;
    this->cols = cols;
}

// --------------------------------------------------------------

template<typename T>
void aghMatrix<T>::destroyMatrixPtr() {
    for (int i = 0; i < this->rows; i++)
        delete[] matrixPtr[i];
    delete[] matrixPtr;
}

// --------------------------------------------------------------

/// \brief Checks if specified element exists in matrix
///
/// \param row - row number
/// \param col - column number
/// \return
/// \li false - if element exists in array
/// \li true - if element does not exist in array
template<typename T>
bool aghMatrix<T>::isInRange(const int row, const int col) const {
    bool rowInRange = (row >= 0) && (row < this->rows);
    bool colInRange = (col >= 0) && (col < this->cols);
    if (!rowInRange || !colInRange) return true;
    return false;
}

// --------------------------------------------------------------

template<typename T>
int aghMatrix<T>::getRows() const {
    return this->rows;
}

// --------------------------------------------------------------

template<typename T>
int aghMatrix<T>::getCols() const {
    return this->cols;
}

// --------------------------------------------------------------

template<typename T>
void aghMatrix<T>::print() const {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++)
            cout << this->matrixPtr[i][j] << " ";
        cout << endl;
    }
}

// --------------------------------------------------------------

template<typename T>
T aghMatrix<T>::getItem(const int row, const int col) const {
    if (this->isInRange(row, col))
        throw aghException(0, "Index out of range", __FILE__, __LINE__);
    return this->matrixPtr[row][col];
}

// --------------------------------------------------------------

template<typename T>
void aghMatrix<T>::setItem(const int row, const int col, const T &value) {
    if (this->isInRange(row, col))
        throw aghException(0, "Index out of range", __FILE__, __LINE__);
    this->matrixPtr[row][col] = value;
    return;
}

// --------------------------------------------------------------

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

// --------------------------------------------------------------

/// \brief Fills matrix with elements provided as method arguments.
///
/// This method utilizes variadic templates to grab all arguments passed
/// and throws them into std::array with initializer list.
/// Afterwards it iterates through it, setting all elements to proper positions.
///
/// \param rows - number of rows needed to hold data.
/// \param cols - number of columns needed to hold data.
/// \param args - (qty: rows * cols) arguments with proper data types.
template<typename T>
template<typename... ARGS>
void aghMatrix<T>::setItems(const int rows, const int cols, ARGS... args) {
    if (matrixPtr) this->destroyMatrixPtr();

    createMatrix(rows, cols);

    this->rows = rows;
    this->cols = cols;

    array<T, sizeof...(args)> unpacked_args{args...}; // where all magic happens

    int row = 0;
    int col = 0;
    for (T arg : unpacked_args) {
        this->matrixPtr[row][col] = arg;
        col++;
        if (col == this->cols) {
            row++;
            col = 0;
        }
    }

    return;
}

// --------------------------------------------------------------

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

// --------------------------------------------------------------

// Specialisation of add() method for char type.
template<>
aghMatrix<char> aghMatrix<char>::add(const aghMatrix<char> &matrix) const;

// --------------------------------------------------------------

// Specialisation of add() method for string type.
template<>
aghMatrix<string> aghMatrix<string>::add(const aghMatrix<string> &matrix) const;

// --------------------------------------------------------------

template<typename T>
aghMatrix<T> aghMatrix<T>::multiply(const aghMatrix<T> &matrix) const {
    bool equalDimensions = this->cols == matrix.getRows();
    if (!equalDimensions)
        throw aghException(1, "Tried to multiply matrices with wrong dimensions!", __FILE__, __LINE__);

    aghMatrix<T> newMatrix(this->rows, matrix.getCols());

    T newValue;

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < matrix.getCols(); ++j) {
            newValue = T(0);
            for (int k = 0; k < this->cols; ++k)
                newValue = newValue + this->matrixPtr[i][k] * matrix.getItem(k, j);
            newMatrix.setItem(i, j, newValue);
        }

    return newMatrix;
}

// --------------------------------------------------------------

// Specialisation of multiply() method for char type.
template<>
aghMatrix<char> aghMatrix<char>::multiply(const aghMatrix<char> &matrix) const;

// --------------------------------------------------------------

// Specialisation of multiply() method for string type.
template<>
aghMatrix<string> aghMatrix<string>::multiply(const aghMatrix<string> &matrix) const;

// --------------------------------------------------------------

template<typename T>
bool aghMatrix<T>::equal(const aghMatrix &matrix) const {
    if (this->rows != matrix.getRows() || this->cols != matrix.getCols())
        return false;

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j)
            if (this->matrixPtr[i][j] != matrix.getItem(i, j))
                return false;

    return true;
}

// --------------------------------------------------------------

template<typename T>
aghMatrix<T> &aghMatrix<T>::overwrite(const aghMatrix<T> &matrix) {
    if (this->matrixPtr != matrix.matrixPtr) {

        if (matrixPtr) this->destroyMatrixPtr();

        this->createMatrix(matrix.getRows(), matrix.getCols());

        for (int i = 0; i < this->rows; ++i)
            for (int j = 0; j < this->cols; ++j)
                this->matrixPtr[i][j] = matrix.getItem(i, j);
    }

    return *this;
}

// --------------------------------------------------------------

template<typename T>
aghMatrix<T> aghMatrix<T>::operator+(const aghMatrix<T> &matrix) const {
    return this->add(matrix);
}

// --------------------------------------------------------------

template<typename T>
aghMatrix<T> aghMatrix<T>::operator*(const aghMatrix<T> &matrix) const {
    return this->multiply(matrix);
}

// --------------------------------------------------------------

template<typename Y>
bool operator==(const aghMatrix<Y> &matrix1, const aghMatrix<Y> &matrix2) {
    return matrix1.equal(matrix2);
}

// --------------------------------------------------------------

template<typename Y>
bool operator!=(const aghMatrix<Y> &matrix1, const aghMatrix<Y> &matrix2) {
    return !(matrix1.equal(matrix2));
}

// --------------------------------------------------------------

template<typename T>
aghMatrix<T> &aghMatrix<T>::operator=(const aghMatrix<T> &matrix) {
    return this->overwrite(matrix);
}

// --------------------------------------------------------------

template<typename T>
T aghMatrix<T>::operator()(const int row, const int col) {
    return this->getItem(row, col);
}

#endif