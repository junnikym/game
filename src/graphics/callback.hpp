#ifndef SCREW_GRAPHICS_CALLBACK_HPP
#define SCREW_GRAPHICS_CALLBACK_HPP

#include "../common.hpp"

namespace graphics { 

#ifdef __OPENGL__

void err_callback(int err_code, const char* err_description);

void frame_buf_size_callback(GLFWwindow* window, int width, int height);

#endif /* __OPENGL__ */

} // end of namespace : graphics

#endif /* ! SCREW_GRAPHICS_CALLBACK_HPP */