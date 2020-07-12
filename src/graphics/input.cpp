#include "input.hpp"

namespace graphics { 

/****************************************************************************
 *	Input			Class
 * 
 *  Process input through graphics lib
 ****************************************************************************/

Input::Input() { }

void Input::initialize() {
	fill_n(m_keys, 256, 0);
}

// ---------- Input's setter 	--------------------------------------------------

void Input::key_down( int& key ) {
	m_keys[key] = 1;
}

void Input::key_up( int& key ) {
	m_keys[key] = 0;
}

// -------------------------------------------------------------------------------//
// ---------- Input's getter 	--------------------------------------------------

int Input::is_key_down( int key ) {
	return m_keys[key];
}

// -------------------------------------------------------------------------------//

} // end of namespace : graphics