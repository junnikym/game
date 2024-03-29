#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "../common.hpp"

#include "camera.hpp"
#include "model.hpp"
#include "callback.hpp"

#include "../input/callback.hpp"
#include "../input/control.hpp"

#include "../physics/entity.hpp"

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
		void set_screen_color( double r, double g, double b, double a );

		int render();

	#ifdef __OPENGL__
		GLFWwindow* get_window();
	#endif /* __OPENGL__ */

	private:
		double screen_color[4] = { 0.0f };

		const int* screen_width;
		const int* screen_height;

	#ifdef __OPENGL__
		GLFWwindow* window;
	#endif /* __OPENGL__ */
};

} // end of namespace : graphics
 
#endif /* ! GRAPHICS_H */