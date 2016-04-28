#ifndef AGH_MATRIX
#define AGH_MATRIX

#include <exception>
#include <stdexcept>

using namespace std;

template <class T> class aghMatrix {
public:
	aghMatrix();

	aghMatrix(int row, int col);

	~aghMatrix();

	int resize(int row, int col);

	void setItem(int row, int col, T value);

	//void setItems();
private:
	T ** matrixPtr;
	int row;
	int col;
}; 


#endif
