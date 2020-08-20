#include "callback.hpp"

namespace graphics { 

#ifdef __OPENGL__

void err_callback(int err_code, const char* err_description) {	
	fprintf(stderr, "Error : %s\n", err_description);				// 에러를 출력
}

void frame_buf_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

#endif /* __OPENGL__ */

} // end of namespace : graphics
