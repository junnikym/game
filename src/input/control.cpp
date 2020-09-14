#include "control.hpp"

namespace input { 

Control::Control(const Input* input_ptr) {
	m_input_ptr = input_ptr;
}

void Control::set_input(const Input* input_ptr) {
	m_input_ptr = input_ptr;
}

/****************************************************************************
 *	FourDirectionControl	| Class
 * 
 *  Forward (Up), BackWard (Down), Left, Right Four Direction
 * Binary Control Module
 ****************************************************************************/

FourDirectionControl::FourDirectionControl(
	const unsigned int& up_key,
	const unsigned int& down_key,
	const unsigned int& left_key,
	const unsigned int& right_key,
	const Input*	   input_ptr
) {
	m_input_ptr = input_ptr;

	m_vertical = new BinaryControl(up_key, down_key);
	m_horizontal = new BinaryControl(right_key, left_key);
}

FourDirectionControl::~FourDirectionControl() {
	this->release();
}

void FourDirectionControl::release() {
	if(m_vertical != nullptr) {
		delete m_vertical;
		m_vertical = nullptr;
	}

	if(m_horizontal != nullptr) {
		delete m_horizontal;
		m_horizontal = nullptr;
	}
}

void FourDirectionControl::update() {
	memset(m_buffer, 0, sizeof(int) * 4);

	int each_buf = 0;

	if(m_horizontal != nullptr && m_vertical != nullptr) {
		each_buf = m_vertical->update(m_input_ptr);

		m_buffer[(int)MOVEMENT_2D_ASIX::vertical] = each_buf;

		each_buf = m_horizontal->update(m_input_ptr);

		m_buffer[(int)MOVEMENT_2D_ASIX::horizontal] = each_buf;
	}

}

void FourDirectionControl::get(int reciver[]) {
	memcpy(reciver, m_buffer, 2 * sizeof(int));
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
				m_key_buf = -m_key_buf;
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
	auto offset =  m_input_ptr->get_mouse_offset();

	m_state[0] += offset[0];
	m_state[1] += offset[1];
}

void MouseControl::get(double reciver[]) {
	memcpy(reciver, m_state, 4 * sizeof(double));
}

} // end of namespace : input