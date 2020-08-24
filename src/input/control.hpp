#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "input.hpp"

#include "../common.hpp"

namespace input { 

Class BinaryControl;

class Control {
	public:
	private:
};

class FourDirectionControl {
	public:
		FourDirectionControl(
			const usigned int& up_key,
			const usigned int& down_key,
			const usigned int& left_key,
			const usigned int& right_key,
			const Input&	   input_ptr
		);

		int show_key() const;

		void update();
		const int[4]& get();
	private:
		const Input* m_input_ptr = nullptr;

		BinaryControl m_vertical;
		BinaryControl m_horizontal;

		int[4] m_buffer = {0};
};

class BinaryControl {
	public:
		BinaryControl(
			const unsigned int& positive_key,
			const unsigned int& negative_key,
			const Input&		input_ptr
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
};

} // end of namespace : input

#endif	/* CONTROL_HPP */