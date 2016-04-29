#ifndef AGH_MATRIX
#define AGH_MATRIX

#include "aghException.h"
#include <iostream>

using namespace std;

template<class T>
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

    aghMatrix add(const aghMatrix &matrix) const;

    aghMatrix subtract(const aghMatrix &matrix) const;

    aghMatrix multiply(const aghMatrix &matrix) const;

    bool equal(const aghMatrix &matrix) const;

    aghMatrix& overwrite(const aghMatrix &matrix);

    aghMatrix operator+(const aghMatrix &matrix) const;

    aghMatrix operator-(const aghMatrix &matrix) const;

    aghMatrix operator*(const aghMatrix &matrix) const;

    bool operator==(const aghMatrix &matrix) const;

    bool operator!=(const aghMatrix &matrix) const;

    aghMatrix& operator=(const aghMatrix &matrix);

    T operator()(const int row, const int col);
    
private:
    T **matrixPtr;
    int rows;
    int cols;

    void createMatrix(const int row, const int col);

    bool checkRowCol(const int row, const int col) const;
};


#endif
