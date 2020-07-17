#include "graphics.hpp"

namespace graphics {

/****************************************************************************
 *	Graphics		Class
 * 
 *  class that handle a graphics lib; 
 ****************************************************************************/

Graphics::Graphics() { }

#ifdef __OPENGL__			// initialize openGL

bool Graphics::initialize( int& screen_width, int& screen_height, const string& app_title ) {

// initialize glfw
	if ( !glfwInit() ) {
		cout << "Failed to initialize GLFW" << endl;
		return false;
	}

// setting
	glfwWindowHint(GLFW_SAMPLES, 4); 								// 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 					// preference version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);					// minimum version
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 			// do not use old content
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

// if not setting screen size -> set to full size
	if( ( ! screen_width ) | ( ! screen_height ) ) {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		screen_width = mode->width;
		screen_height = mode->height;
	}

// Create Window, OpenGL Content
	this->window = glfwCreateWindow( screen_width, screen_height, app_title.c_str(), NULL, NULL);
	if( this->window == NULL ){
		cout << "Failed to open GLFW window." << endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(this->window);

// initislize GLFW
	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		cout << "Failed to initialize GLEW." << endl;
		return false;
	}

// set callback functions
	glfwSetKeyCallback(this->window, key_callback);
	glfwSetCursorPosCallback(this->window, mouse_cursor_callback);
	glfwSetScrollCallback(this->window, mouse_scroll_callback);
	glfwSetFramebufferSizeCallback(this->window, frame_buf_size_callback);

// activate VSYNC
	glfwSwapInterval(1);

	return true;
}

#endif /* __OPENGL__ , __DX__ */

bool Graphics::shutdonw() {
	#ifdef __OPENGL__
		glfwTerminate();
	#endif /* __OPENGL__ */

	return true;
}

void Graphics::set_screen_color( float r, float g, float b, float a) {
	screen_color[0] = r;		screen_color[1] = g;
	screen_color[2] = b;		screen_color[3] = a;
}


void Graphics::clear_screen() {
	glClearColor ( screen_color[0], screen_color[1], screen_color[2], screen_color[3] );
	glClear ( GL_COLOR_BUFFER_BIT );
}

int Graphics::render() {
	// -- render begin 	--------------------------------------------------
	#ifdef __OPENGL__	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
	#endif /* __OPENGL__ */
	// -------------------------------------------------------------------//
	
	// -- render 		--------------------------------------------------
		/*   ...   */
	// -------------------------------------------------------------------//

	// -- render begin 	--------------------------------------------------
	#ifdef __OPENGL__	
		glfwSwapBuffers(this->window);
		return glfwWindowShouldClose(this->window);
	#endif /* __OPENGL__ */
	// -------------------------------------------------------------------//

	return 1;	// do not close window
}

} // end of namespace : graphics