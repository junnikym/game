#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../common.hpp"

#include "../math/vector.hpp"
#include "../input/control.hpp"

namespace phy {

class Entity {
	public:
		Entity(const math::Vector<double>& position);
		Entity(const math::Vector<double>& position, double angle);

		math::Vector<double> position() const;
		double angle() const;

		void position(math::Vector<double> position);
		void angle(double angle);

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
		using DictControl = std::vector< std::pair< input::ControlType, input::Control > >;
		void input_updater(DictControl& controller);

	private:
		string m_model;

		// Entity State
		math::Vector<double> m_position;
		double m_angle;

		DictControl m_controller;
};

} // end of namespace : phy

#endif