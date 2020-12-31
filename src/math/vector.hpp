// implementation of vector.h

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "vector.h"

namespace math {

template <class T>
Vector<T>::Vector(const Vector<T>& other) {
	this->resize(other.size());
	this->memory.assign(other.memory.begin(), other.memory.end());
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> il) : memory(il) {
	m_size = il.size();
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
double Vector<T>::length() {
	double result = 0.0;

	for(auto it : memory)
		result += it * it;
	
	return std::sqrt(result);
}

/* ==================================================
 * Convert Fucntions
 ================================================== */

template <class T>
void Vector<T>::to_arr(T reciver[]) {
	for(int i = 0; i < m_size; i++) 
		reciver[i] = memory.get[i];
}

template <class T>
void Vector<T>::normalize() {
	double length = this->length();

	for(auto& it : memory)
		it /= length;
}

template <class T>
Vector<T> Vector<T>::get_normalize() {
	Vector<T> result = *this;
	return std::move(result.normalize());
}

template <class T>
double Vector<T>::dot(const Vector<T>& v1, const Vector<T>& v2) {
	double result = 0;

	for(int i = 0; i < v1.size(); i++) {
		result += v1.get(i) * v2.get(i);
	}

	return std::move(result);
}

template <class T>
double Vector<T>::abs_dot(const Vector<T>& v1, const Vector<T>& v2) {
	return std::abs(Vector<T>::dot(v1, v2));
}

template <class T>
void Vector<T>::rotation(
	double x, double y, double z,
	const bool& is_radian
) {
	if( !is_radian ){
		x = to_radians(x);
		y = to_radians(y);
		z = to_radians(z);
	}

	this->rotation_x(x);
	this->rotation_x(y);
	this->rotation_x(z);
}

template <class T>
void Vector<T>::rotation(double angle, const bool& is_radian) {
	if( !is_radian )
		angle = to_radians(angle);

	this->rotation_z(angle);
}

//static
template <class T>
math::Vector<T>* Vector<T>::rotation (
	math::Vector<T>* p_out,
	const double& x, const double& y, const double& z,
	const bool& is_radian
) {
	p_out->rotation(x, y, z, is_radian);
	return p_out;
}

//static
template <class T>
math::Vector<T>* Vector<T>::rotation (
	math::Vector<T>* p_out,
	const double& angle,
	const bool& is_radian
) {
	p_out->rotation(angle, is_radian);
	return p_out;
}

//static
template <class T>
math::Vector<T> Vector<T>::rotation_copy(
	const math::Vector<T>& vector,
	const double& x, const double& y, const double& z,
	const bool& is_radian
) {
	math::Vector<T> result(vector);
	result.rotation(x, y, z, is_radian);
	return std::move(result);
}

//static
template <class T>
math::Vector<T> Vector<T>::rotation_copy(
	const math::Vector<T>& vector,
	const double& angle,
	const bool& is_radian
) {
	math::Vector<T> result(vector);
	result.rotation(angle, is_radian);
	return std::move( result );
}

template <class T>
void Vector<T>::rotation_x(const double& angle) {
	Matrix<double> rotation_mat {
		{1			, 0				, 0				, 0},
		{0			, cos(angle)	, sin(angle)	, 0},
		{0			, -sin(angle)	, cos(angle)	, 0},
		{0			, 0				, 0				, 1},
	};

	*this *= rotation_mat;
}

template <class T>
void Vector<T>::rotation_y(const double& angle) {
	Matrix<double> rotation_mat {
		{cos(angle)	, 0				, -sin(angle)	, 0},
		{0			, 1				, 0				, 0},
		{sin(angle)	, 0				, cos(angle)	, 0},
		{0 			, 0				, 0				, 1},
	};

	*this *= rotation_mat;
}

template <class T>
void Vector<T>::rotation_z(const double& angle) {
	Matrix<double> rotation_mat {
		{cos(angle)	, sin(angle)	, 0				, 0},
		{-sin(angle), cos(angle)	, 0				, 0},
		{0			, 0				, 1				, 0},
		{0 			, 0				, 0				, 1},
	};

	*this *= rotation_mat;
}

template <class T>
math::Vector<double>* Vector<T>::move (
	math::Vector<T>* p_out,
	const math::Vector<T>& to_where
) {
	(*p_out) += to_where;
	return p_out;
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

template <class T>
void Vector<T>::resize( size_t_r size ) {
	this->memory.resize(size);
	this->m_size = size;
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
	for(int i = 0; i < m_size; i++) {
		memory[i] *= rhs.get(i);
	}

	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator /= (const Vector& rhs) {
	for(int i = 0; i < m_size; i++) {
		memory[i] /= rhs.get(i);
	}

	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator += (const T& rhs) {
	for(int i = 0; i < m_size; i++) {
		memory[i] += rhs;
	}

	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator -= (const T& rhs) {
	for(int i = 0; i < m_size; i++) {
		memory[i] -= rhs;
	}

	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator *= (const T& rhs) {
	for(int i = 0; i < m_size; i++) {
		memory[i] *= rhs;
	}

	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator /= (const T& rhs) {
	for(int i = 0; i < m_size; i++) {
		memory[i] /= rhs;
	}

	return *this;
}

// Vector<T>& operator += (const Matrix<T>& rhs);
// Vector<T>& operator -= (const Matrix<T>& rhs);

template <class T>
Vector<T>& Vector<T>::operator *= (const Matrix<T>& rhs) {
	T elem = 0;

	for(int row = 0; row < m_size; row++) {

		elem = 0;
		for(int col = 0; col < m_size; col++) 
			elem += rhs.get(row, col) * memory[col];

		memory[row] = elem;

	}

	return *this;
}

// Vector<T>& operator /= (const Matrix<T>& rhs);

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

template <class T>
const Vector<T> Vector<T>::operator + (const T& rhs) const {
	return Vector<T>(*this) += rhs;
}

template <class T>
const Vector<T> Vector<T>::operator - (const T& rhs) const {
	return Vector<T>(*this) -= rhs;
}

template <class T>
const Vector<T> Vector<T>::operator * (const T& rhs) const {
	return Vector<T>(*this) *= rhs;
}

template <class T>
const Vector<T> Vector<T>::operator / (const T& rhs) const {
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