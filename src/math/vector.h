#ifndef VECTOR_H
#define VECTOR_H

#include "math_alias.hpp"

namespace math {


template<class T>
class Vector {
	public:
		Vector(size_t_r size);

		size_t size() const;

		T get(const unsigned int& index) const;

		void resize( size_t_r size );

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