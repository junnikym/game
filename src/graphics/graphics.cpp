#include "graphics.hpp"

namespace graphics {

extern std::vector<Camera> g_cams;
extern std::map<string, Model> g_models;
extern std::map<string, Shader> g_shaders;

/****************************************************************************
 *	Graphics		Class
 * 
 *  class that handle a graphics lib; 
 ****************************************************************************/

Graphics::Graphics() { }

#ifdef __OPENGL__			// initialize openGL

bool Graphics::initialize( int& screen_width, int& screen_height, const string& app_title ) {

	// initialize glfw
	//----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 
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
	//----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 
	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		cout << "Failed to initialize GLEW." << endl;
		return false;
	}

	// set callback functions
	glfwSetKeyCallback(this->window, input::key_callback);
	glfwSetCursorPosCallback(this->window, input::mouse_cursor_callback);
	glfwSetScrollCallback(this->window, input::mouse_scroll_callback);
	glfwSetFramebufferSizeCallback(this->window, frame_buf_size_callback);

	// activate VSYNC
	glfwSwapInterval(1);

	// STB
	stbi_set_flip_vertically_on_load(true);

	// early depth testing
	glEnable(GL_DEPTH_TEST);

	this->screen_width = &screen_width;
	this->screen_height = &screen_height;

// ----- ---------- ---------- ---------- ----- //
// -- for testing	---------- ---------- ---- //
	g_shaders.insert( 
		pair<string, Shader>(
			"default",
			Shader(
				"resource/shader/default_vertex.vs", 
				"resource/shader/default_fragment.fs"
	)));

	g_models.insert(
		pair<string, Model>(
			"cube",
			Model("resource/object/backpack/backpack.obj")
	));
// ----- ---------- ---------- ---------- ----- //
// ----- ---------- ---------- ---------- ---- //

	return true;
}

#endif /* __OPENGL__ , __DX__ */

bool Graphics::shutdonw() {

	for (auto it : g_shaders) {
		it.second.shutdown();
	}

	#ifdef __OPENGL__
		glfwTerminate();
	#endif /* __OPENGL__ */

	return true;
}

void Graphics::set_screen_color( double r, double g, double b, double a) {
	screen_color[0] = move(r);		screen_color[1] = move(g);
	screen_color[2] = move(b);		screen_color[3] = move(a);
}


void Graphics::clear_screen() {
	glClearColor ( screen_color[0], screen_color[1], screen_color[2], screen_color[3] );
	glClear ( GL_COLOR_BUFFER_BIT );
}

int Graphics::render() {

	// -- render begin
	// -------------------------------------------------------------------//
	#ifdef __OPENGL__	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// ----- ---------- ---------- ---------- ----- //
// -- for testing	---------- ---------- ---- //

// @ TODO : delete

	Shader& finded_shader = g_shaders.find("default")->second;
	finded_shader.use();
 
	matrix4 projection = perspective<double>( radians(g_cams[0].get_zoom()), (double)(*screen_width) / (double)(*screen_height), 0.1f, 100.0f);

	matrix4 view = g_cams[0].get_view();

	finded_shader.set_mat4("projection", projection);
	finded_shader.set_mat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	finded_shader.set_mat4("model", model);

	g_models.find("cube")->second.draw( finded_shader );
/*
	g_shaders.use();

	matrix4 projection = perspective<double>( radians(g_cams.get_zoom()), (double)(*screen_width) / (double)(*screen_height), 0.1f, 100.0f);
	matrix4 view = g_cams.get_view();

	g_shaders.set_mat4("projection", projection);
	g_shaders.set_mat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	g_shaders.set_mat4("model", model);

	g_models.draw(g_shaders);
*/
// ----- ---------- ---------- ---------- ----- //
// ----- ---------- ---------- ---------- ---- //



	#endif /* __OPENGL__ */
	
	// -- render
	// -------------------------------------------------------------------//

	// -- render begin
	// -------------------------------------------------------------------//
	#ifdef __OPENGL__	
		glfwSwapBuffers(this->window);
		glfwPollEvents();

		return glfwWindowShouldClose(this->window);
	#endif /* __OPENGL__ */

	return 1;	// maintain a loop 
}

#ifdef __OPENGL__
	GLFWwindow* Graphics::get_window() {
		return this->window;
	}
#endif /* __OPENGL__ */

} // end of namespace : graphics