#ifndef AGH_MATRIX
#define AGH_MATRIX

#include "aghException.h"
#include <iostream>

using namespace std;

template <class T> class aghMatrix {
public:
	aghMatrix();

	aghMatrix(int rows, int cols);

	~aghMatrix();

	void setItem(int row, int col, T value);

	//void setItems();
private:
	T ** matrixPtr;
	int rows;
	int cols;

    void createMatrix(int row, int col);
}; 


#endif
