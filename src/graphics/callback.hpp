#ifndef CALLBACK_H

#include "common.hpp"

#include "input.hpp"

namespace graphics { 

#ifdef __OPENGL__

extern INPUT g_input_msger;

void err_callback(int err_code, const char* err_description);

void key_callback(GLFWwindow* window, int key, int scan_code, int action, int mods);

void mouse_cursor_callback(GLFWwindow* window, double pos_x, double pos_y);

void mouse_scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

void frame_buf_size_callback(GLFWwindow* window, int width, int height);

#endif /* __OPENGL__ */

} // end of namespace : graphics

#endif /* ! CALLBACK_H */