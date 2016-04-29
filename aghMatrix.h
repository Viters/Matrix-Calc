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

    void setItem(const int row, const int col, const T &value);

    void setItems(const T * value);
private:
    T **matrixPtr;
    int rows;
    int cols;

    void createMatrix(int row, int col);
};


#endif
