#ifndef MATRIX_H
#define MATRIX_H

#include "math_alias.hpp"

namespace math {

template <class T>
class Matrix {
	public:
		// proxy for index operator
		class IndexProxy;

	public:
		Matrix(size_t_r row, size_t_r col);

		size_t row() const;
		size_t col() const;
		T get(const unsigned int& row, const unsigned int col) const;
		T get_directly(const unsigned int& index) const;

		void resize( size_t_r row, size_t_r col);
		void resize_col( size_t_r col );
		void resize_row( size_t_r row );

	// Compound Assignment
		Matrix<T>& operator += (const Matrix& rhs);
		Matrix<T>& operator -= (const Matrix& rhs);
		Matrix<T>& operator *= (const Matrix& rhs);
		Matrix<T>& operator /= (const Matrix& rhs);

	// Binary Arithmetic
		const Matrix<T> operator + (const Matrix& rhs) const;
		const Matrix<T> operator - (const Matrix& rhs) const;
		const Matrix<T> operator * (const Matrix& rhs) const;
		const Matrix<T> operator / (const Matrix& rhs) const;

	// Comparison
		bool operator == (const Matrix &other) const;
		bool operator != (const Matrix &other) const;

	// Index
		IndexProxy operator [] (const int& index);

	private:
		std::vector<T> memory;
		size_t m_row = 0, m_col = 0;

	public:
	
	// proxy for index operator
		class IndexProxy {
			public:
				IndexProxy(
					std::vector<T>& memory_ptr, 
					const int& primary_index, 
					size_t_r row_size
				) : 
					m_memory_ptr(memory_ptr), 
					m_primary_index(primary_index),
					m_row_size(row_size) 
				{ }

				T& operator [] (const int& index) {
					int i = m_primary_index * m_row_size + index;
					return m_memory_ptr[i];
				}

			private:
				std::vector<T>& m_memory_ptr;
				const int& m_primary_index = 0;
				size_t_r m_row_size = 0;
		};
};

template< class T >
std::ostream& operator<<(std::ostream& output, const Matrix<T>& v);


}	// end of namespace (math)

#endif	/* MATRIX_H */