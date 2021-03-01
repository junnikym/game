// implementation of matrix.h

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "matrix.h"

namespace math {

/*
template <class T>
Matrix<T>::
*/

/* ==================================================
 * Constructor
 ================================================== */

template <class T>
Matrix<T>::Matrix(size_t_r row, size_t_r col) {
	this->memory.resize(row * col);
	this->m_row = row;	this->m_col = col;
}

template <class T>
Matrix<T>::Matrix(VecIniter<T> il) {
	m_row = il.size();
	m_col = il.begin()->size();

	for(auto& it : il) {
		memory.insert(memory.end(), it.begin(), it.end());
	}
}

template <class T>
void Matrix<T>::resize_col( size_t_r col ) {

}

template <class T>
void Matrix<T>::resize_row( size_t_r row ) {

}

/* ==================================================
 * Get functions
 ================================================== */

template <class T>
size_t Matrix<T>::row() const {
	return m_row;
}

template <class T>
size_t Matrix<T>::col() const {
	return m_row;
}

template <class T>
T Matrix<T>::get(const unsigned int& row, const unsigned int& col) const {
	return memory[ m_row * col + row ];
}

template <class T>
T Matrix<T>::get_directly(const unsigned int& index) const {
	return memory[index];
}

/* ==================================================
 * Compound Assignment
 ================================================== */

template <class T>
Matrix<T>& Matrix<T>::operator += (const Matrix& rhs) {

}

template <class T>
Matrix<T>& Matrix<T>::operator -= (const Matrix& rhs) {

}

template <class T>
Matrix<T>& Matrix<T>::operator *= (const Matrix& rhs) {

}

template <class T>
Matrix<T>& Matrix<T>::operator /= (const Matrix& rhs) {

}

/* ==================================================
 * Binary Arithmetic
 ================================================== */

template <class T>
const Matrix<T> Matrix<T>::operator + (const Matrix& rhs) const {
	return Matrix<T>(*this) += rhs;
}

template <class T>
const Matrix<T> Matrix<T>::operator - (const Matrix& rhs) const {
	return Matrix<T>(*this) -= rhs;
}

template <class T>
const Matrix<T> Matrix<T>::operator * (const Matrix& rhs) const {
	return Matrix<T>(*this) *= rhs;
}

template <class T>
const Matrix<T> Matrix<T>::operator / (const Matrix& rhs) const {
	return Matrix<T>(*this) /= rhs;
}

/* ==================================================
 * Comparison
 ================================================== */

template <class T>
bool Matrix<T>::operator == (const Matrix &other) const {
	int lhs_size = m_row * m_col;
	int rhs_size = other.row() * other.col();

	if(lhs_size != rhs_size) {
		return false;
	}

	for(int i = 0; i < lhs_size; i++) {
		if( this->memory[i] != other.get_directly(i) )
			return false;
	}

	return true;
}

template <class T>
bool Matrix<T>::operator != (const Matrix &other) const {
	return !(*this == other);
}

/* ==================================================
 * Index
 ================================================== */

template <class T>
typename Matrix<T>::IndexProxy Matrix<T>::operator [] (const int& index) {
	return IndexProxy(memory, index, m_row);
}

/* ==================================================
 * Output
 ================================================== */

template <class T>
std::ostream& operator<<(std::ostream& output, const Matrix<T>& v) {

	for( int r = 0; r < v.row(); r++ ) {
		for( int c = 0; c < v.col(); c++ )
			output << v[r][c] << " ";
		
		output << "\n";
	}
	
	output << std::flush;

	return output;
}


}	// end of namespace (math)

#endif	/* MATRIX_HPP */