#ifndef VECTOR_H
#define VECTOR_H

#include "math_alias.hpp"
#include "../common.hpp"
#include "../integrate_types.hpp"

#include "matrix.hpp"

#include <initializer_list>

namespace math {


template<class T>
class Vector {
	public:
		Vector() = default;
		Vector(size_t_r size);
		Vector(const Vector<T>& other);
		Vector(std::initializer_list<T> il);
		Vector(const T arr[]);
		Vector(const vector3& vec);

		// Get Functions
		size_t size() const;
		T get(const unsigned int& index) const;
		double length();

		// Set Functions
		void resize( size_t_r size );
		void append( T elem );
		void set_zero();

		// Convert Functions
		void to_arr(T reciver[]);

		void normalize();
		Vector<T> get_normalize();

		static double dot(const Vector<T>& v1, const Vector<T>& v2);
		static double abs_dot(const Vector<T>& v1, const Vector<T>& v2);

		/**
		 * @brief Rotation function for Over the 3D
		 * 
		 * @param x x-axis rotation angle
		 * @param y y-axis rotation angle
		 * @param z z-axis rotation angle
		 * @param is_radian rotation angle's value is radina -> true, or degree -> false (default : false)
		 */
		void rotation(
			double x, double y, double z,
			const bool& is_radian = false
		);
		
		/**
		 * @brief Rotation on 2D Coord
		 * 
		 * @param angle rotation angle
		 * @param is_radian rotation angle's value is radina -> true, or degree -> false (default : false)
		 */
		void rotation(double angle, const bool& is_radian = false);

		/**
		 * @brief Rotation function for Over the 3D
		 * 
		 * @param p_out object address for result
		 * @param x x-axis rotation angle
		 * @param y y-axis rotation angle
		 * @param z z-axis rotation angle
		 * @param is_radian is Angle Param radian?
		 * @return p_out
		 */
		static math::Vector<T>* rotation (
			math::Vector<T>* p_out,
			const double& x, const double& y, const double& z,
			const bool& is_radian = false
		);

		/**
		 * @brief Rotation on 2D Coord
		 * 
		 * @param p_out object address for result
		 * @param angle rotation angle
		 * @param is_radian is Angle Param radian?s
		 * @return math::Vector<T>* 
		 */
		static math::Vector<T>* rotation (
			math::Vector<T>* p_out,
			const double& angle,
			const bool& is_radian = false
		);

		/**
		 * @brief Rotation function for Over the 3D -> returning result
		 * 
		 * @param vector base model
		 * @param x x-axis rotation angle
		 * @param y y-axis rotation angle
		 * @param z z-axis rotation angle
		 * @param is_radian is Angle Param radian?
		 * @return math::Vector<T> type return
		 */
		static math::Vector<T> rotation_copy (
			const math::Vector<T>& vector,
			const double& x, const double& y, const double& z,
			const bool& is_radian = false
		);

		/**
		 * @brief Rotation on 2D -> returning result
		 * 
		 * @param vector base model
		 * @param angle rotation angle
		 * @param is_radian is Angle Param radian?
		 * @return math::Vector<T> type return
		 */
		static math::Vector<T> rotation_copy (
			const math::Vector<T>& vector,
			const double& angle,
			const bool& is_radian = false
		);

		static math::Vector<double>* move (
			math::Vector<T>* p_out,
			const math::Vector<T>& to_where
		);

	private:
		void rotation_x(const double& angle);
		void rotation_y(const double& angle);
		void rotation_z(const double& angle);

	public:	

	// assignment operator
		Vector<T>& operator = (const vector3& rhs);

	// Compound Assignment
		Vector<T>& operator += (const Vector& rhs);
		Vector<T>& operator -= (const Vector& rhs);
		Vector<T>& operator *= (const Vector& rhs);
		Vector<T>& operator /= (const Vector& rhs);

		Vector<T>& operator += (const T& rhs);
		Vector<T>& operator -= (const T& rhs);
		Vector<T>& operator *= (const T& rhs);
		Vector<T>& operator /= (const T& rhs);

		Vector<T>& operator += (const Matrix<T>& rhs);
		Vector<T>& operator -= (const Matrix<T>& rhs);
		Vector<T>& operator *= (const Matrix<T>& rhs);
		Vector<T>& operator /= (const Matrix<T>& rhs);

	// Binary Arithmetic
		const Vector<T> operator + (const Vector& rhs) const;
		const Vector<T> operator - (const Vector& rhs) const;
		const Vector<T> operator * (const Vector& rhs) const;
		const Vector<T> operator / (const Vector& rhs) const;

		const Vector<T> operator + (const T& rhs) const;
		const Vector<T> operator - (const T& rhs) const;
		const Vector<T> operator * (const T& rhs) const;
		const Vector<T> operator / (const T& rhs) const;

	// Comparison
		bool operator == (const Vector &other) const;
		bool operator != (const Vector &other) const;

	// Index
		T& operator [] (const int& index);

		vector3 convert_to_vec3();

	private:
		std::vector<T> memory;
		size_t m_size = 0;

	/**
	 * Memmory member alias
	 *  -> like x, y, z, a or yaw, pitch, roll ...
	 */
	public:
		T& x() { return memory[0]; }
		T& y() { return memory[1]; }
		T& z() { return memory[2]; }
};

template<typename T>
using MathVecList = std::vector< math::Vector<T> >;

}	// end of namespace (math)

#endif /* VECTOR_H */