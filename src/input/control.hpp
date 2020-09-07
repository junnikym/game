#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "input.hpp"

#include "../common.hpp"

namespace input { 

class Control;
class BinaryControl;

using ControlPtr = std::shared_ptr<Control>;

class Control {
	public:
		virtual ~Control() { }
		
		virtual void update() { }
		virtual void get(int reciver[]) { }
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
		const Input* m_input_ptr = nullptr;

		BinaryControl* m_vertical = nullptr;
		BinaryControl* m_horizontal = nullptr;

		int m_buffer[2] = {0};
};

class BinaryControl {
	public:
		BinaryControl(
			const unsigned int& positive_key,
			const unsigned int& negative_key,
			const Input*		input_ptr
		);

		void positive_key(const unsigned int& positive_key);
		void negative_key(const unsigned int& negative_key);

		int positive_key() const;
		int negative_key() const;

		void input(const Input* input);

		int update();
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

} // end of namespace : input

#endif	/* CONTROL_HPP */