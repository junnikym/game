#include "entity.hpp"

namespace phy {

Entity::Entity(const math::Vector<double> position) {
	m_position = std::move(position);

	this->initialize();
}

Entity::Entity(const math::Vector<double> position, math::Vector<double> angle) {
	m_position = std::move(position);
	m_angle = std::move(angle);

	this->initialize();
}

Entity::~Entity() {
	release();
}

void Entity::initialize(){
	m_front = normalize( m_front );
	m_right = normalize( cross(m_front, m_up) );
	m_up 	= normalize( cross(m_right, m_front) );
}

void Entity::release() {

	for( auto it : m_force ) {
		delete it.second;
	}

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

	append_control_force(contorller_title);

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

	m_front.x = cos( radians(m_angle[YAW]) ) * cos( radians(m_angle[PITCH]) );
	m_front.y = sin( radians(m_angle[PITCH]) );
	m_front.z = sin( radians(m_angle[YAW]) ) * cos( radians(m_angle[PITCH]) );
	
	m_front = normalize( m_front );
	m_right = normalize( cross(m_front, m_world_up) );
	m_up 	= normalize( cross(m_right, m_front) );
}

void Entity::input_updater(DictControlIt& it) {

	switch(it->first) {
		case input::ControlType::FourDirection:
		{
			int reciver[3] = { 0, };
			it->second->get_offset(reciver);

			auto offset  = m_right 	* (float)reciver[0];
				 offset += m_front 	* (float)reciver[1];
				 offset += m_up		* (float)reciver[2];

			m_4d_force_ptr->set_vec( offset );
			m_position += m_4d_force_ptr->get();
			
			return;
		}
		
		case input::ControlType::MouseRotation:
		{
			double reciver[4] = { 0.0, };
			it->second->get_offset(reciver);

			m_angle[0] += reciver[0];
			m_angle[1] += reciver[1];

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

void Entity::append_control_force(const input::ControlType& controller_type) {
	switch(controller_type) {
		case input::ControlType::FourDirection:
		{
			if(m_4d_force_ptr != nullptr)
				return;

			m_force.push_back( make_pair<string, Force*>(
				"Controller_4D", new Accelator( {1, 0, 0}, 100 )
			));

			m_4d_force_ptr = m_force.back().second;

			return;
		}

		case input::ControlType::MouseRotation:
		{
			return;
		}

		default:
			break;
	}
}


} // end of namespace : phy