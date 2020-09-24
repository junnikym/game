#include "callback.hpp"

namespace input {


#ifdef __OPENGL__

	Input g_input_msger;

	void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods) {

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)		// ESC | PRESS
			glfwSetWindowShouldClose(window, GLFW_TRUE);		//     -> close window

		if (action == GLFW_PRESS)
			g_input_msger.key_down( key );
		
		if (action == GLFW_RELEASE)
			g_input_msger.key_up( key );
	}

	void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
		g_input_msger.update_mouse_scroll(x_offset, y_offset);
	}

#endif /* __OPENGL__ or __DX__ */


} // end of namespace : input