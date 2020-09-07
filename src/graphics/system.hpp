#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "graphics.hpp"

using namespace input;
using namespace phy;

namespace graphics { 

#ifdef __OPENGL__
	extern Input g_input_masger;
#endif

class System {
	public:
		System();
		System( const System& );
		System( string title, int width, int height );

		bool initialize();
		void shutdown();

	// -- setter fuctions --
		void set_title( const char* title );
		void set_screen_size(int width, int height);

		void run();

	private:
		string m_app_title;
		int screen_width = 0;
		int screen_height = 0;

		Graphics* 	m_graphics;
		Input* 		m_input;

	/**
	 * @ TODO : Delete under the code line
	 * 			this code wrotten only for test
	 */
		ControlPtr main_cam_controller = nullptr;
		Entity main_cam = Entity(math::Vector<double>{0, 0, 3});
};

} // end of namespace : graphics

#endif /* ! SYSTEM_HPP */