#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "../common.hpp"
#include "../math/vector.hpp"

#include <iostream>

namespace phy {

using math::MathVecList;

/**
 * Single shape's archetype class
 */
class Shape {
	private:
		math::Vector<double> m_center_of_gravity;
		MathVecList<double> m_verties;
	public:
		Shape() = delete;
		Shape(MathVecList<double> verties);
		Shape(std::initializer_list<math::Vector<double>> il);

		const math::Vector<double>* get_center();

		size_t get_n_vertex();
		auto get_vertex(int i);
		const MathVecList<double>* get_verties() const;

		Shape ratation(
			const double& x, const double& y, const double& z,  
			const bool& is_radian = false,
			const math::Vector<double>* center = nullptr
		);

		Shape ratation(
			const double& angle,
			const bool& is_radian = false,
			const math::Vector<double>* center = nullptr
		);

		Shape* rotation(
			Shape* p_out,
			const double& x, const double& y, const double& z,  
			const bool& is_radian = false,
			const math::Vector<double>* center = nullptr
		);

		Shape* rotation(
			Shape* p_out,
			const double& angle,
			const bool& is_radian = false,
			const math::Vector<double>* center = nullptr
		);

	private:
		template < class ... Args >
		void rotation_splitter( Shape* p_out,
								const math::Vector<double>* center, 
								const Args& ... args );

	public:
		// Shape&& Move( const math::Vector<double>& pos );

	private:
		void calc_center();
};

} // end of namespace : phy

#endif // end of SHAPE_HPP