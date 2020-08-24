#include "control.hpp"

namespace input { 


FourDirectionControl::FourDirectionControl(
	const usigned int& up_key,
	const usigned int& down_key,
	const usigned int& left_key,
	const usigned int& right_key,
	const Input&	   input_ptr
) {
	m_vertical.positive_key(up_key);
	m_vertical.negative_key(down_key);

	m_horizontal.positive_key(right_key);
	m_horizontal.negative_key(left_key);

	this->m_input_ptr = input_ptr;
}

void FourDirectionControl::update() {
	memset(m_buffer, 0, sizeof(int) * 4);

	int each_buf = 0;

	each_buf = m_vertical.update();

	if(each_buf > 0)
		m_buffer[MOVEMENT::forward] = 1;
	else if(each_buf < 0) 
		m_buffer[MOVEMENT::backward] = 1;

	each_buf = m_horizontal.update();

	if(each_buf > 0)
		m_buffer[MOVEMENT::right] = 1;
	else if(each_buf < 0) 
		m_buffer[MOVEMENT::left] = 1;
}

const int[4]& FourDirectionControl::get() {
	return this->m_buffer;
}

BinaryControl::BinaryControl(
	const unsigned int& positive_key,
	const unsigned int& negative_key,
	const Input&		input_ptr
) {
	this->m_positive_key = (int)positive_key;
	this->m_negative_key = (int)negative_key;
	this->m_input_ptr 	 = input_ptr;
}

void BinaryControl::positive_key(const unsigned int& positive_key) {
	this->m_positive_key = positive_key;
}

void BinaryControl::negative_key(const unsigned int& negative_key) {
	this->m_negative_key = negative_key;
}

int BinaryControl::positive_key() const {
	return m_positive_key;
}

int BinaryControl::negative_key() const {
	return m_negative_key
}

void BinaryControl::input(const Input* input) {
	this->m_input_ptr = input;
}

int BinaryControl::update() {

	// Positive key pressed
	// -------------------------------------------------------
	if(m_input_ptr->is_key_down(m_positive_key)) {

		// if Negative key is not pressed before
		// assign positive value to key buffer
		if(m_key_buf == 0)
			m_key_buf = 1;
	}
	else 
		m_key_buf = 0;

	// Negative key pressed
	// -------------------------------------------------------
	if(m_input_ptr->is_key_down(m_negative_key)) {
		if(m_key_buf == 0) {
			m_key_buf = -1;
		}
	}
	else 
		m_key_buf = 0;

	return m_key_buf;
}

int BinaryControl::get() {
	return m_key_buf;
}


} // end of namespace : input