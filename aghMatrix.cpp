#include "aghMatrix.h"

//template<>
//aghMatrix aghMatrix<const char>::add(const aghMatrix<const char> &matrix) const {
//    bool equalRows = this->rows == matrix.getRows();
//    bool equalCols = this->cols == matrix.getCols();
//    if (!equalRows || !equalCols)
//        throw aghException(1, "Tried to add matrices with wrong dimensions!", __FILE__, __LINE__);
//
//    aghMatrix<int> newMatrix(this->rows, this->cols);
//
//    for (int i = 0; i < this->rows; ++i)
//        for (int j = 0; j < this->cols; ++j)
//            newMatrix.setItem(i, j, int(this->matrixPtr[i][j]) - 97 + int(matrix->getItem(i, j)) - 97);
//
//    return newMatrix;
//}

//template<>
//aghMatrix aghMatrix<string>::operator+(const aghMatrix &matrix) const{
//    bool equalRows = this->rows == matrix.getRows();
//    bool equalCols = this->cols == matrix.getCols();
//    if (!equalRows || !equalCols)
//        throw aghException(1, "Tried to add matrices with wrong dimensions!", __FILE__, __LINE__);
//    aghMatrix <string>newMatrix(this->rows, this->cols);
//    int i, j;
//    for(i=0; i<this->rows; ++i)
//        for(j=0; j<this->cols; ++j){
//            newMatrix.setItem(i, j, combineCollections(this->getItem(i,j), matrix.getItem(i,j));
//        }
//    return newMatrix;
//}

//template<>
//aghMatrix aghMatrix<string>::operator*(const aghMatrix &matrix) const{
//    bool correctDimensions = this->cols == matrix.getRows();
//    if(!correctDimensions)
//        throw aghException(1, "Tried to multiply matrices with wrong dimensions!", __FILE__, __LINE__);
//    aghMatrix <string>newMatrix(this->rows, matrix.getCols());
//    int i, j, k;
//    string tmp;
//    for(i =0; i<this->rows, i++)
//        for(j=0; j<matrix.getCols(); j++){
//            tmp="";
//            for(k=0; k<this->cols; k++){
//                tmp=combineCollections(tmp, combineCollections(this->matrixPtr[i][k], matrix.getItem(k, j)));
//            }
//            newMatrix.setItem(i, j, tmp);
//        }
//    return newMatrix;
//}

