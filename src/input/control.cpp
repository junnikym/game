#include "control.hpp"

namespace input { 


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