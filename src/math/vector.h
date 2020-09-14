#ifndef VECTOR_H
#define VECTOR_H

#include "math_alias.hpp"

namespace math {


template<class T>
class Vector {
	public:
		Vector() = default;
		Vector(size_t_r size);
		Vector(const Vector<T>& other);
		Vector(std::initializer_list<T> il);
		Vector(const T arr[]);

		size_t size() const;

		T get(const unsigned int& index) const;
		void to_arr(T reciver[]);

		double length();

		void normalize();
		Vector<T> get_normalize();

		void resize( size_t_r size );
		void append( T elem );

	// Compound Assignment
		Vector<T>& operator += (const Vector& rhs);
		Vector<T>& operator -= (const Vector& rhs);
		Vector<T>& operator *= (const Vector& rhs);
		Vector<T>& operator /= (const Vector& rhs);

	// Binary Arithmetic
		const Vector<T> operator + (const Vector& rhs) const;
		const Vector<T> operator - (const Vector& rhs) const;
		const Vector<T> operator * (const Vector& rhs) const;
		const Vector<T> operator / (const Vector& rhs) const;

	// Comparison
		bool operator == (const Vector &other) const;
		bool operator != (const Vector &other) const;

	// Index
		T& operator [] (const int& index);

	private:
		std::vector<T> memory;
		size_t m_size = 0;
};


}	// end of namespace (math)

#endif /* VECTOR_H */