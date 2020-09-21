// implementation of vector.h

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "vector.h"

namespace math {

template <class T>
Vector<T>::Vector(const Vector<T>& other) {
	this->m_size = other.m_size;
	this->memory.resize(m_size);
	
	this->memory.assign(other.memory.begin(), other.memory.end());

//	for(int i = 0; i < m_size; i++) {
//		ref_for_alias[i] = &this->memory[i];
//	}
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> il) : memory(il) {
	m_size = il.size();

//	for(int i = 0; i < m_size; i++) {
//		ref_for_alias[i] = &this->memory[i];
//	}
}

template <class T>
Vector<T>::Vector(const T arr[]) {
	memory = std::vector(std::begin(arr), std::end(arr));
}

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

template <class T>
void Vector<T>::to_arr(T reciver[]) {
	for(int i = 0; i < m_size; i++) 
		reciver[i] = memory.get[i];
}

template <class T>
double Vector<T>::length() {
	double result = 0.0;

	for(auto it : memory)
		result += it;
	
	return result /= this->size();
}

template <class T>
void Vector<T>::normalize() {
	double length = this->length();

	for(auto it : memory)
		it /= length;
}

template <class T>
Vector<T> Vector<T>::get_normalize() {
	Vector<T> result = *this;
	return std::move(result.normalize());
}

/* ==================================================
 * Set functions
 ================================================== */

template <class T>
void Vector<T>::append( T elem ) {
	this->memory.push_back( move(elem) );

	if(m_size < 4) {
		this->ref_for_alias[m_size] = &this->memory[m_size];
	}

	m_size++;
}

/* ==================================================
 * Compound Assignment
 ================================================== */

template <class T>
Vector<T>& Vector<T>::operator += (const Vector& rhs) {
	for(int i = 0; i < m_size; i++) {
		memory[i] += rhs.get(i);
	}

	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator -= (const Vector& rhs) {
	for(int i = 0; i < m_size; i++) {
		memory[i] -= rhs.get(i);
	}

	return *this;
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
	return memory[index];
}

template <class T>
vector3 Vector<T>:: convert_to_vec3() {
	vector3 result = {
		this->memory[0],
		this->memory[1],
		this->memory[2]
	};

	return result;
}

}	// end of namespace (math)

#endif	/* VECTOR_HPP */