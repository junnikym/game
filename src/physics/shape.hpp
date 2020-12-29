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
	// < Meber Fields >
	//--------------------------------------------------
	private:
		math::Vector<double> m_center_of_gravity;
		MathVecList<double> m_verties;

	// < Constructor >
	//--------------------------------------------------
	public:
		Shape() = delete;
		Shape(MathVecList<double> verties);
		Shape(std::initializer_list<math::Vector<double>> il);

		Shape(
			MathVecList<double> verties, 
			const math::Vector<double>* center
		);

	// < Getters >
	//--------------------------------------------------
	public:
		const math::Vector<double>* get_center();

		size_t get_n_vertex();
		auto get_vertex(int i);
		const MathVecList<double>* get_verties() const;

		template < class... Args >
		using TransFunc = std::function< math::Vector<double>* (math::Vector<double>*, const Args&...) >;

		template < class... Args >
		Shape* transform(
			Shape* p_out,
			TransFunc<Args...> func,
			const Args&... args
		);

	// < etc >
	//--------------------------------------------------
	private:
		void calc_center();
};


// < implementations of Transfrom Function >
//--------------------------------------------------

template < class... Args > 
Shape* Shape::transform (
	Shape* p_out,
	Shape::TransFunc<Args...> func,
	const Args&... args
) {
	if(p_out->get_n_vertex() != m_verties.size())
		p_out->m_verties = m_verties;

	for(int i = 0; i < m_verties.size(); i++)
		func( &(p_out->m_verties[i]), args... );

	return p_out;
}


} // end of namespace : phy

#endif // end of SHAPE_HPP