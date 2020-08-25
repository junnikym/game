#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../common.hpp"

#include "../math/vector.hpp"
#include "../input/control.hpp"

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
			const char* contorller_title,
			const input::Control* controller,
			bool overlap = false
		);

		void remove_controller ( 
			const char* contorller_title,
			bool include_overlap = false
		);

		void remove_controller (
			const char* contorller_title,
			const int& index
		);

	private:
		string m_model;

		// Entity State
		math::Vector<double> m_position;
		double m_angle;

		DictVector<const input::Control*> m_controller;
};

#endif