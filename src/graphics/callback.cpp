#include "callback.hpp"

namespace graphics { 

#ifdef __OPENGL__

INPUT g_input_msger;

void err_callback(int err_code, const char* err_description) {	
	fprintf(stderr, "Error : %s\n", err_description);				// 에러를 출력
}

void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)		// ESC | PRESS
		glfwSetWindowShouldClose(window, GLFW_TRUE);		//     -> close window

	if (action == GLFW_PRESS)
		g_input_msger.key_down( key );
	
	if (action == GLFW_RELEASE)
		g_input_msger.key_up( key );
}

void mouse_cursor_callback(GLFWwindow* window, double pos_x, double pos_y) {
}

void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
}

void frame_buf_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

#endif /* __OPENGL__ */

} // end of namespace : graphics
