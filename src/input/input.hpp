#ifndef INPUT_H
#define INPUT_H

#include "../common.hpp"
#include "../math/vector.hpp"

namespace input { 

class Input {
	public:
		Input() = default;

		void initialize(const double& cursor_x, const double& cursor_y); 
		
	// -- setter fuctions --
		void key_down( int& key ); 
		void key_up( int& key ); 

		void update_mouse_pos(const double& x, const double& y);
		void update_mouse_scroll(const double& x, const double& y);
		
	// -- getter fuctions --
		int is_key_down( int key ) const;

		math::Vector<double> get_mouse_pos() const;
		math::Vector<double> get_mouse_scroll() const;
		math::Vector<double> get_mouse_offset() const;

	private:
		int m_keys[512];
		DEVICE* m_window;

		math::Vector<double> m_mouse_pos = {0, 0};
		math::Vector<double> m_mouse_scroll = {0, 0};

		math::Vector<double> m_mouse_offset = {0, 0};
};

} // end of namespace : input

#endif /* INPUT_H */