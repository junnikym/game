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

Shape Shape::ratation(
	const double& x, const double& y, const double& z,
	const bool& is_radian,
	const math::Vector<double>* center
) {
	Shape result(m_verties);

	this->rotation_splitter (
		&result, 
		(center == nullptr ? &m_center_of_gravity : center), 
		x, y, z, is_radian
	);
	return std::move(result);
}

Shape Shape::ratation(
	const double& angle,
	const bool& is_radian,
	const math::Vector<double>* center
) {
	Shape result(m_verties);

	this->rotation_splitter (
		&result, 
		(center == nullptr ? &m_center_of_gravity : center), 
		angle, is_radian 
	);
	
	return std::move(result);
}

//static
Shape* Shape::rotation(
	Shape* p_out,
	const double& x, const double& y, const double& z,  
	const bool& is_radian,
	const math::Vector<double>* center
) {
	this->rotation_splitter (
		p_out, 
		(center == nullptr ? p_out->get_center() : center), 
		x, y, z, is_radian
	);

	return p_out;
}

//static
Shape* Shape::rotation(
	Shape* p_out,
	const double& angle,
	const bool& is_radian,
	const math::Vector<double>* center
) {
	this->rotation_splitter (
		p_out, 
		(center == nullptr ? p_out->get_center() : center), 
		angle, is_radian
	);
	
	return p_out;
}

//static
template < class ... Args >
void Shape::rotation_splitter( Shape* p_out,
							   const math::Vector<double>* center, 
							   const Args& ... args ) {
	if(p_out->get_n_vertex() != m_verties.size())
		p_out->m_verties = m_verties;

	for(int i = 0; i < m_verties.size(); i++) {
		p_out->m_verties[i] = m_verties[i] - *center;
		p_out->m_verties[i].rotation(args...);
	}
}

// Shape&& Shape::Move( const math::Vector<double>& pos ) {
// 	MathVecList<double> result = m_verties;

// 	for()
// }

void Shape::calc_center() {
	m_center_of_gravity.resize( m_verties[0].size() );

	for(const auto& it : m_verties) {
		m_center_of_gravity += it;
	}

	m_center_of_gravity /= m_verties.size();
}

} // end of namespace : phy