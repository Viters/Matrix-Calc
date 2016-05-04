#include "aghMatrix.h"

/// \brief Specialisation of add() method for char type.
///
/// This method calculates sum of chars interpreting them as natural numbers.
/// (a = 0, b = 1, c = 2 etc.) Result is calculated as modulo of 26, so "z + z" will
/// still yield letter from <a, z>.
///
/// \return Matrix with char elements
template<>
aghMatrix<char> aghMatrix<char>::add(const aghMatrix<char> &matrix) const {
    bool equalRows = this->rows == matrix.getRows();
    bool equalCols = this->cols == matrix.getCols();
    if (!equalRows || !equalCols)
        throw aghException(1, "Tried to add matrices with wrong dimensions!", __FILE__, __LINE__);

    aghMatrix<char> newMatrix(this->rows, this->cols);

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j)
            newMatrix.setItem(i, j, (char) ((this->matrixPtr[i][j] + matrix.getItem(i, j) - 194) % 26 + 97));

    return newMatrix;
}

// --------------------------------------------------------------

/// \brief Specialisation of add() method for char type.
///
/// This method calculates multiplication of chars interpreting them as natural numbers,
/// (a = 0, b = 1, c = 2 etc.) utilizing usual matrix multiplication alghoritm.
/// Result is calculated as modulo of 26, so "z * z" will still yield letter from <a, z>.
///
/// \return Matrix with char elements
template<>
aghMatrix<char> aghMatrix<char>::multiply(const aghMatrix<char> &matrix) const {
    bool correctDimensions = this->cols == matrix.getRows();
    if (!correctDimensions)
        throw aghException(1, "Tried to multiply matrices with wrong dimensions!", __FILE__, __LINE__);

    aghMatrix<char> newMatrix(this->rows, matrix.getCols());

    int newValue;

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < matrix.getCols(); ++j) {
            newValue = 0;
            for (int k = 0; k < this->cols; ++k)
                newValue = newValue + (this->matrixPtr[i][k] - 97) * (matrix.getItem(k, j) - 97);
            newMatrix.setItem(i, j, (char) (newValue % 26 + 97));
        }

    return newMatrix;
}

// --------------------------------------------------------------

/// \brief Specialisation of add() method for string type.
///
/// This method calculates sum of letter's sets within corresponding elements.
///
/// \return Matrix with string elements
template<>
aghMatrix<string> aghMatrix<string>::add(const aghMatrix<string> &matrix) const {
    bool equalRows = this->rows == matrix.getRows();
    bool equalCols = this->cols == matrix.getCols();
    if (!equalRows || !equalCols)
        throw aghException(1, "Tried to add matrices with wrong dimensions!", __FILE__, __LINE__);

    aghMatrix<string> newMatrix(this->rows, this->cols);
    int i, j;
    for (i = 0; i < this->rows; ++i)
        for (j = 0; j < this->cols; ++j) {
            newMatrix.setItem(i, j, combineCollections(this->getItem(i, j), matrix.getItem(i, j)));
        }
    return newMatrix;
}

// --------------------------------------------------------------

/// \brief Specialisation of add() method for string type.
///
/// This method calculates intersection of letter's sets within corresponding elements
/// utilizing usual matrix multiplication alghoritm.
///
///
/// \return Matrix with string elements
template<>
aghMatrix<string> aghMatrix<string>::multiply(const aghMatrix<string> &matrix) const {
    bool correctDimensions = this->cols == matrix.getRows();
    if (!correctDimensions)
        throw aghException(1, "Tried to multiply matrices with wrong dimensions!", __FILE__, __LINE__);

    aghMatrix<string> newMatrix(this->rows, matrix.getCols());
    int i, j, k;
    string tmp;
    for (i = 0; i < this->rows; i++)
        for (j = 0; j < matrix.getCols(); j++) {
            tmp = "";
            for (k = 0; k < this->cols; k++) {
                tmp = combineCollections(tmp, intersectCollections(this->matrixPtr[i][k], matrix.getItem(k, j)));
            }
            newMatrix.setItem(i, j, tmp);
        }
    return newMatrix;
}

