#include "entity.hpp"

namespace phy {

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
	int control_reciver[2] = { 0, };

	for (auto it = m_controller.begin(); it != m_controller.end(); it++) {
		it->second->get(control_reciver);
		
	//	cout << "controller : " << control_reciver[0] << ", " << control_reciver[1] << endl;

		/**
		 * @ TODO : Delete under the code line
		 * 			this code wrotten only for test
		 */

		m_position[0] -= control_reciver[0];
		m_position[1] -= control_reciver[1];

		// --------------- until here ---------------
	}
}

void Entity::input_updater(DictControl& controller) {

}

} // end of namespace : phy