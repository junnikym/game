#ifndef INPUT_H
#define INPUT_H

#include "common.hpp"

namespace graphics { 

class Input {
	public:
		Input();

		void initialize(); 
		
	// -- setter fuctions --
		void key_down( int& key ); 
		void key_up( int& key ); 
		
	// -- getter fuctions --
		int is_key_down( int key );

	private:
		int m_keys[512];
};

} // end of namespace : graphics

#endif /* INPUT_H */