#include "control.hpp"

namespace input { 

Control::Control(const Input* input_ptr) {
	m_input_ptr = input_ptr;
}

void Control::set_input(const Input* input_ptr) {
	m_input_ptr = input_ptr;
}

/****************************************************************************
 *	ThreeWayControl	| Class
 * 
 *  Forward (Up), BackWard (Down), Left, Right Four Direction
 * Binary Control Module
 ****************************************************************************/

ThreeWayControl::ThreeWayControl(
	const unsigned int& front_key,
	const unsigned int& back_key,
	const unsigned int& left_key,
	const unsigned int& right_key,
	const unsigned int& up_key,
	const unsigned int& down_key,
	const Input*	   input_ptr
) {
	m_input_ptr = input_ptr;

	m_front = new BinaryControl(front_key, back_key);
	m_right = new BinaryControl(right_key, left_key);
	m_up = new BinaryControl(up_key, down_key);
}

ThreeWayControl::~ThreeWayControl() {
	this->release();
}

void ThreeWayControl::release() {
	if(m_front != nullptr) {
		delete m_front;
		m_front = nullptr;
	}

	if(m_right != nullptr) {
		delete m_right;
		m_right = nullptr;
	}

	if(m_up != nullptr) {
		delete m_up;
		m_up = nullptr;
	}
}

void ThreeWayControl::update() {
	m_buffer.set_zero();
	double each_buf = 0;

	if(m_right != nullptr && m_front != nullptr && m_up != nullptr) {
		each_buf = (double)m_front->update(m_input_ptr);
		m_buffer[(int)MOVEMENT_DIRECTION::right] = each_buf;

		each_buf = (double)m_right->update(m_input_ptr);
		m_buffer[(int)MOVEMENT_DIRECTION::front] = each_buf;

		each_buf = (double)m_up->update(m_input_ptr);
		m_buffer[(int)MOVEMENT_DIRECTION::up] = each_buf;
	}

}

void ThreeWayControl::get_offset(int reciver[]) {
	reciver[0] = m_buffer[0];
	reciver[1] = m_buffer[1];
	reciver[2] = m_buffer[2];
}

/****************************************************************************
 *	BinaryControl			| Class
 * 
 *  
 ****************************************************************************/

BinaryControl::BinaryControl(
	const unsigned int& positive_key,
	const unsigned int& negative_key
) {
	this->m_positive_key = (int)positive_key;
	this->m_negative_key = (int)negative_key;
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
	return m_negative_key;
}

int BinaryControl::update(const Input* input_ptr) {
	int positive = input_ptr->is_key_down(m_positive_key);
	int negative = input_ptr->is_key_down(m_negative_key);
	int pressed = positive + negative;

	if(pressed) {

		// Both key pressed
		// --------------------------------------------------
		if( pressed == 2 ) {
			if(m_backup_buf == 0) {
				m_backup_buf = m_key_buf;
				m_key_buf 	 = -m_key_buf;
			}
		}

		// Only one key pressed
		// --------------------------------------------------
		else {
			pressed = positive - negative;
			
			m_key_buf = pressed;
			m_backup_buf = 0;
		}
	}
	// Nothing pressed
	// --------------------------------------------------
	else {
		m_key_buf = 0;
		m_backup_buf = 0;
	}

	return m_key_buf;
}

int BinaryControl::get() {
	return m_key_buf;
}

/****************************************************************************
 *	MouseControl			| Class
 * 
 *  
 ****************************************************************************/

MouseControl::MouseControl(const Input* input_ptr) {
	m_input_ptr = input_ptr;
}

void MouseControl::set_speed(double cursor, double zoom) {
	m_cursor_speed = std::move(cursor);
	m_zoom_speed = std::move(zoom);
}

void MouseControl::update() {
	m_offset =  m_input_ptr->get_mouse_offset() * m_cursor_speed;
}

void MouseControl::get_offset(double reciver[]) {
	reciver[0] = m_offset[0];
	reciver[1] = m_offset[1];
}

} // end of namespace : input