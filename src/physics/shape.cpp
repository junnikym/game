#include "shape.hpp"

namespace phy {

Shape::Shape(MathVecList<double> verties) 
	: m_verties( std::move(verties)) {
	calc_center();
}

Shape::Shape(std::initializer_list<math::Vector<double>> il) 
	: m_verties(std::move(il)) {
	calc_center();
}

Shape::Shape(
	MathVecList<double> verties, 
	const math::Vector<double>* center
) : m_verties( std::move(verties) ),
	m_center_of_gravity( *center ) { }

const math::Vector<double>* Shape::get_center() {
	return &m_center_of_gravity;
}

size_t Shape::get_n_vertex() {
	return m_verties.size();
}

auto Shape::get_vertex(int i) {
	return m_verties[i];
}

const MathVecList<double>* Shape::get_verties() const {
	return &m_verties;
}

void Shape::calc_center() {
	m_center_of_gravity.resize( m_verties[0].size() );

	for(const auto& it : m_verties) {
		m_center_of_gravity += it;
	}

	m_center_of_gravity /= m_verties.size();
}

} // end of namespace : phy