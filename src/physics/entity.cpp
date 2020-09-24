#include "entity.hpp"

namespace phy {

Entity::Entity(const math::Vector<double>& position) {
	m_position = math::Vector<double>(position);
}

Entity::Entity(const math::Vector<double>& position, math::Vector<double>& angle) {
	m_position = math::Vector<double>(position);
	m_angle = math::Vector<double>(angle);
}

math::Vector<double> Entity::position() const {
	return m_position;
}

math::Vector<double> Entity::angle() const {
	return m_angle;
}

void Entity::position(math::Vector<double> position) {
	m_position = std::move(position);
}

void Entity::angle(math::Vector<double> angle){
	m_angle = std::move(angle);
}

bool Entity::append_controller(
	input::ControlType contorller_title,
	input::ControlPtr& controller,
	bool overlap
) {
	if(!overlap) {
		for(auto it : m_controller) {
			if(it.first == contorller_title) {
					return false;
			}
		}
	}

	m_controller.push_back( 
		std::move( std::make_pair(
			std::move(contorller_title), 
			controller
		) )
	);
	
	return true;
}

void Entity::remove_controller ( 
	input::ControlType& contorller_title,
	bool include_overlap
) {
	for(auto it = m_controller.begin(); it != m_controller.end(); it++) {
		if(it->first == contorller_title) {
			m_controller.erase(it);

			if(!include_overlap) {
				return;
			}
		}
	}
}

void Entity::remove_controller (
	input::ControlType& contorller_title,
	const int& index
) {
	int passed_index = 0;

	for(auto it = m_controller.begin(); it != m_controller.end(); it++) {
		if(it->first == contorller_title) {
			
			if(passed_index == index) 
				m_controller.erase(it);
			else
				passed_index++;

		}
	}
}

void Entity::update() {

	/* --------------------------------------------------
		Update Entity's State Form Controllers
	 -------------------------------------------------- */
	for (auto it = m_controller.begin(); it != m_controller.end(); it++) {
		this->input_updater(it);
	}

	/* --------------------------------------------------
		Calcuate this entity's 3way direction
		( front, rigth, up )

	 * x asix : cos( yaw ) * cos ( pitch )
	 * y asix : sin( pitch )
	 * z asix : sin( yaw ) * cos ( pitch )
	 -------------------------------------------------- */
	m_angle[1] += 1;
	vector3 axis = m_angle.convert_to_vec3();

	m_front.x = cos( radians(axis.x) ) * cos( radians(axis.y) );
	m_front.y = sin( radians(axis.y) );
	m_front.z = sin( radians(axis.x) ) * cos( radians(axis.y) );

	m_front = normalize(this->m_front);
	m_right = normalize( cross(m_front, m_up) );
	m_up 	= normalize( cross(m_right, m_front) );
}

void Entity::input_updater(DictControlIt& it) {

	switch(it->first) {
		case input::ControlType::FourDirection:
		{
			int reciver[2] = { 0, };
			it->second->get(reciver);

			// !TODO : classify movement like smooth, normal...
			m_position[0] -= reciver[0];
			m_position[1] -= reciver[1];
			
			return;
		}
		
		case input::ControlType::MouseRotation:
		{
			double reciver[4] = { 0.0, };
			it->second->get(reciver);

			m_angle[0] = std::move(reciver[0]);
			m_angle[1] = std::move(reciver[1]);
			//m_angle[2] = std::move(reciver[2]);

			/**
			 * !TODO : Zoom; 
			 * 		   calc the front vector -> move entity as much as reciver[4]
			 */

			return;
		}
		
		default:
			break;
	}

	return;
}


} // end of namespace : phy