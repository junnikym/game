#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../common.hpp"

#include "../math/vector.hpp"
#include "../input/control.hpp"

namespace phy {

using namespace input;

class Entity {
	public:
		Entity(const math::Vector<double>& position);
		Entity(const math::Vector<double>& position, math::Vector<double>& angle);

		math::Vector<double> position() const;
		math::Vector<double> angle() const;		

		void position(math::Vector<double> position);
		void angle(math::Vector<double> angle);

		void set_model(const string& model);

		bool append_controller(
			input::ControlType contorller_title,
			input::ControlPtr& controller,
			bool overlap = false
		);

		void remove_controller ( 
			input::ControlType& contorller_title,
			bool include_overlap = false
		);

		void remove_controller (
			input::ControlType& contorller_title,
			const int& index
		);

		void update();
	private:
		void input_updater(DictControlIt& it);

	private:
		string m_model;

		// Entity State
		math::Vector<double> m_position = {0.0, 0.0, 0.0};
		math::Vector<double> m_angle = {0.0, 0.0, 0.0};

		DictControl m_controller;

	/**
	 *  The members for graphics
	 */
	private:
		vector3 m_front = {0.0, 0.0, -1.0};
		vector3 m_right = {0.0, 0.0, 0.0};
		vector3 m_up	 = {0.0, 1.0, 0.0};

	public:
		vector3 front() const { return m_front; }
		vector3 right() const { return m_right; }
		vector3 up() 	const { return m_up; }
};

} // end of namespace : phy

#endif