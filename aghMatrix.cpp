#include "aghMatrix.h"

template<>
aghMatrix<char> aghMatrix<char>::add(const aghMatrix<char> &matrix) const {
    bool equalRows = this->rows == matrix.getRows();
    bool equalCols = this->cols == matrix.getCols();
    if (!equalRows || !equalCols)
        throw aghException(1, "Tried to add matrices with wrong dimensions!", __FILE__, __LINE__);

    aghMatrix<char> newMatrix(this->rows, this->cols);

    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < this->cols; ++j)
            newMatrix.setItem(i, j, int(this->matrixPtr[i][j]) - 97 + int(matrix.getItem(i, j)) - 97);

    return newMatrix;
}

template<>
aghMatrix<std::string> aghMatrix<std::string>::add(const aghMatrix<std::string> &matrix) const{
    bool equalRows = this->rows == matrix.getRows();
    bool equalCols = this->cols == matrix.getCols();
    if (!equalRows || !equalCols)
        throw aghException(1, "Tried to add matrices with wrong dimensions!", __FILE__, __LINE__);
    aghMatrix<std::string> newMatrix(this->rows, this->cols);
    int i, j;
    for(i=0; i<this->rows; ++i)
        for(j=0; j<this->cols; ++j){
            newMatrix.setItem(i, j, combineCollections(this->getItem(i,j), matrix.getItem(i,j)));
        }
    return newMatrix;
}

template<>
aghMatrix<std::string> aghMatrix<std::string>::multiply(const aghMatrix<std::string> &matrix) const{
    bool correctDimensions = this->cols == matrix.getRows();
    if(!correctDimensions)
        throw aghException(1, "Tried to multiply matrices with wrong dimensions!", __FILE__, __LINE__);
    aghMatrix<std::string> newMatrix(this->rows, matrix.getCols());
    int i, j, k;
    std::string tmp;
    for(i =0; i<this->rows; i++)
        for(j=0; j<matrix.getCols(); j++){
            tmp="";
            for(k=0; k<this->cols; k++){
                tmp=combineCollections(tmp, combineCollections(this->matrixPtr[i][k], matrix.getItem(k, j)));
            }
            newMatrix.setItem(i, j, tmp);
        }
    return newMatrix;
}

