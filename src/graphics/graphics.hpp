#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "common.hpp"

#include "callback.hpp"

namespace graphics {

class Graphics {
	public:
		Graphics();
		Graphics( const Graphics& );

	#ifdef __OPENGL__
		bool initialize( int& screen_width, int& screen_height, const string& app_title );
	#elif __DX__
		
	#endif

		bool shutdonw();

		void clear_screen();
		void set_screen_color( float r, float g, float b, float a );

		int render();

	private:
		float screen_color[4] = { 0.0f };

	#ifdef __OPENGL__
		GLFWwindow* window;
	#endif /* __OPENGL__ */
};

} // end of namespace : graphics
 
#endif /* ! GRAPHICS_H */