#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "input.hpp"

#include "../common.hpp"

namespace input { 

enum class ControlType {
	FourDirection,
	MouseRotation,
};

class Control;
class BinaryControl;
class ThreeWayControl;
class MouseControl;

using ControlPtr = std::shared_ptr<Control>;
using DictControlType = std::pair< input::ControlType, ControlPtr >;
using DictControl = std::vector< DictControlType >;
using DictControlIt = DictControl::iterator;

class Control {
	public:
		Control() = default;
		Control(const Input* input_ptr);
		virtual ~Control() { }
		
		virtual void update() { }
		virtual void get_offset(int reciver[]) { }
		virtual void get_offset(double reciver[]) { }

		void set_input(const Input* input_ptr);
	protected:
		const Input* m_input_ptr = nullptr;
};

class ThreeWayControl : public Control {
	public:
		ThreeWayControl(
			const unsigned int& front_key,
			const unsigned int& back_key,
			const unsigned int& left_key,
			const unsigned int& right_key,
			const unsigned int& up_key,
			const unsigned int& down_key,
			const Input*		input_ptr
		);

		~ThreeWayControl();

		void release();

		int show_key() const;

		/**
		 *  inheritance from Control class
		 */
		void update();
		void get_offset(int reciver[]);
		 
	private:
		BinaryControl* m_right	= nullptr;
		BinaryControl* m_front	= nullptr;
		BinaryControl* m_up 	= nullptr;

		math::Vector<double> m_buffer = {0.0, 0.0, 0.0};
};

class BinaryControl {
	public:
		BinaryControl(
			const unsigned int& positive_key,
			const unsigned int& negative_key
		);

		void positive_key(const unsigned int& positive_key);
		void negative_key(const unsigned int& negative_key);

		int positive_key() const;
		int negative_key() const;


		int update(const Input*	input_ptr);
		int get();

	private:
		const Input* m_input_ptr = nullptr;

		int m_positive_key = -1;
		int m_negative_key = -1;

		/**
		 *	m_key_buf :
		 *		value < 0  : negative
		 *		value > 0  : positive
		 * 		value == 0 : nothing activate
		 */
		int m_key_buf = 0;
		int m_backup_buf = 0;
};

class MouseControl : public Control {
	public:
		MouseControl(const Input* input_ptr);

		void set_speed(double cursor, double zoom);

		/**
		 *  inheritance from Control class
		 */
		void update();
		void get_offset(double reciver[]);

		/**	
		 * setting member :
		 * 	@ Type : BitFlag
		 */
		int setting = 0;
	private:
		// speed : angle per mouse move 1 pixel
		double m_cursor_speed = 0.1;
		double m_zoom_speed = 1;

		math::Vector<double> m_offset;
};



} // end of namespace : input

#endif	/* CONTROL_HPP */