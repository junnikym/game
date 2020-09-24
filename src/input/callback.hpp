#ifndef SCREW_INPUT_CALLBACK_HPP
#define SCREW_INPUT_CALLBACK_HPP

#include "input.hpp"

namespace input { 


#ifdef __OPENGL__

	extern Input g_input_msger;

	void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);

	void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

#endif /* __OPENGL__ or __DX__ */


} // end of namespace : input

#endif /* ! SCREW_INPUT_CALLBACK_HPP */