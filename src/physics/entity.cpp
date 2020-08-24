#include "entity.hpp"

Entity::Entity(const math::Vector<double>& position) {
	m_position = math::Vector<double>(position);
}

Entity::Entity(const math::Vector<double>& position, double angle) {
	m_position = math::Vector<double>(position);
	this->m_angle 		= std::move(angle);
}

math::Vector<double> Entity::position() const {
	return m_position;
}

double Entity::angle() const {
	return m_angle;
}

void Entity::position(math::Vector<double> position) {
	m_position = std::move(position);
}

void Entity::angle(double angle){
	m_angle = std::move(angle);
}