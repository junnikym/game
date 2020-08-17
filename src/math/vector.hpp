// implementation of vector.h

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "vector.h"

namespace math {


/* ==================================================
 * Get functions
 ================================================== */

template <class T>
size_t Vector<T>::size() const {
	return this->m_size;
}

template <class T>
T Vector<T>::get(const unsigned int& index) const {
	return this->memory[index];
}

/* ==================================================
 * Compound Assignment
 ================================================== */

template <class T>
Vector<T>& Vector<T>::operator += (const Vector& rhs) {

}

template <class T>
Vector<T>& Vector<T>::operator -= (const Vector& rhs) {

}

template <class T>
Vector<T>& Vector<T>::operator *= (const Vector& rhs) {

}

template <class T>
Vector<T>& Vector<T>::operator /= (const Vector& rhs) {

}

/* ==================================================
 * Binary Arithmetic
 ================================================== */

template <class T>
const Vector<T> Vector<T>::operator + (const Vector& rhs) const {
	return Vector<T>(*this) += rhs;
}

template <class T>
const Vector<T> Vector<T>::operator - (const Vector& rhs) const {
	return Vector<T>(*this) -= rhs;
}

template <class T>
const Vector<T> Vector<T>::operator * (const Vector& rhs) const {
	return Vector<T>(*this) *= rhs;
}

template <class T>
const Vector<T> Vector<T>::operator / (const Vector& rhs) const {
	return Vector<T>(*this) /= rhs;
}

/* ==================================================
 * Comparison
 ================================================== */

template <class T>
bool Vector<T>::operator == (const Vector &other) const {
	if( this->size() != other.m_size() )
		return false;

	for(int i = 0; i < m_size; i++) {
		if( memory(i) != other.get(i))
			return false;
	}

	return true;
}

template <class T>
bool Vector<T>::operator != (const Vector &other) const {
	return !(*this == other);
}

/* ==================================================
 * Index
 ================================================== */

template <class T>
T& Vector<T>::operator [] (const int& index) {
	return &this->memory[index];
}


}	// end of namespace (math)

#endif	/* VECTOR_HPP */