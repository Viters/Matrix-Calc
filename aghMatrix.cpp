#include "aghMatrix.h"

template <class T> aghMatrix<T>::aghMatrix() {
	this->resize(10, 10);
}

template <class T> aghMatrix<T>::aghMatrix(int row, int col) {
	this->resize(row, col);
}

template <class T> aghMatrix<T>::~aghMatrix() {
	for (int i = 0; i < this->row; i++)
		delete [] matrixPtr[i];
	delete [] matrixPtr;
}

template <class T> void aghMatrix<T>::resize(int row, int col) {
	try {	
		this->matrixPtr = new T*[row];
		for (int i = 0; i < row; i++)
			this->matrixPtr[i] = new T[col];
		this->row = row;
		this->col = col;
	}
	catch (runtime_error &e) {
		cout << "Błąd podczas tworzenia macierzy: " << e.what() << endl;
	}
}

template <class T> void aghMatrix<T>::setItem(int row, int col, T & value) {
	try {
		this->matrixPtr[row][col] = value;
	}
	catch (runtime_error &e) {
		cout << "Błąd podczas ustawiania elementu: " << e.what() << endl;
	}
	return;
}
