#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "common.hpp"

#include "graphics.hpp"

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

		Graphics* m_graphics;
		Input* m_input;
};

} // end of namespace : graphics

#endif /* ! SYSTEM_HPP */