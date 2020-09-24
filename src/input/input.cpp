#include "input.hpp"

namespace input { 

/****************************************************************************
 *	Input			Class
 * 
 *  Process input through graphics lib
 ****************************************************************************/

void Input::initialize(const double& cursor_x, const double& cursor_y) {
	fill_n(m_keys, 256, 0);
	m_mouse_pos = {cursor_x, cursor_y};
}

// ---------- Input's setter 	--------------------------------------------------

void Input::key_down( int& key ) {
	m_keys[key] = 1;
}

void Input::key_up( int& key ) {
	m_keys[key] = 0;
}

void Input::update_mouse_pos( const double& x, const double& y ) {
	math::Vector<double> current_pos={x, y};
	
	m_mouse_offset = current_pos - m_mouse_pos;

	m_mouse_pos = move(current_pos);
}

void Input::update_mouse_scroll(const double& x, const double& y) {
	m_mouse_scroll = { x, y };
}

// -------------------------------------------------------------------------------//
// ---------- Input's getter 	--------------------------------------------------

int Input::is_key_down( int key ) const {
	return m_keys[key];
}

math::Vector<double> Input::get_mouse_pos() const {
	return m_mouse_pos;
}

math::Vector<double> Input::get_mouse_scroll() const {
	return m_mouse_scroll;
}

math::Vector<double> Input::get_mouse_offset() const {
	return m_mouse_offset;
}

// -------------------------------------------------------------------------------//

} // end of namespace : input