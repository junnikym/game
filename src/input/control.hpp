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
class FourDirectionControl;
class MouseControl;

using ControlPtr = std::shared_ptr<Control>;

class Control {
	public:
		Control() = default;
		Control(const Input* input_ptr);
		virtual ~Control() { }
		
		virtual void update() { }
		virtual void get(int reciver[]) { }
		virtual void get(double reciver[]) { }

		void set_input(const Input* input_ptr);
	protected:
		const Input* m_input_ptr = nullptr;
};

class FourDirectionControl : public Control {
	public:
		FourDirectionControl(
			const unsigned int& up_key,
			const unsigned int& down_key,
			const unsigned int& left_key,
			const unsigned int& right_key,
			const Input*		input_ptr
		);

		~FourDirectionControl();

		void release();

		int show_key() const;

		/**
		 *  inheritance from Control class
		 */
		void update();
		void get(int reciver[]);
		 
	private:
		BinaryControl* m_vertical = nullptr;
		BinaryControl* m_horizontal = nullptr;

		int m_buffer[2] = {0};
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
		void get(double reciver[]);

	private:
		// speed : angle per mouse move 1 pixel
		double m_cursor_speed = 1;
		double m_zoom_speed = 1;
		
		// { pitch, yaw, roll, zoom }
		double m_state[4] = {0, 0, 0, 0};
};



} // end of namespace : input

#endif	/* CONTROL_HPP */