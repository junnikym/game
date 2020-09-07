#include "system.hpp"

namespace graphics {

extern std::vector<Camera> g_cams;

/****************************************************************************
 *	SYTEM			Class
 * 
 *  The system that using graphics lib; 
 ****************************************************************************/

System::System () {
	this->m_app_title = "";

	m_graphics = nullptr;
	m_input = nullptr;
}

System::System ( string title, int width, int height ) {
	this->m_app_title = title;
	this->screen_width = width;
	this->screen_height = height;

	m_graphics = nullptr;
	m_input = nullptr;
}

bool System::initialize() {
	bool result = true;
	
	// m_graphics init
	//--------------------------------------------------

	m_graphics = new Graphics;
	if(m_graphics == nullptr) 
		return false;

	result = m_graphics->initialize( screen_width, screen_height, m_app_title );	
	if( ! result ) 
		return false;

	// input init
	//--------------------------------------------------
	#ifdef __OPENGL__
		m_input = &g_input_msger;
	#else
		m_input = new Input;
		if(m_input == nullptr) 
			return false;
	#endif /* __OPENGL, else */

	m_graphics->set_screen_color(0.1, 0.1, 0.1, 1.0);

	/**
	 * @ TODO : Delete under the code line
	 * 			this code wrotten only for test
	 */
	main_cam_controller = ControlPtr( new FourDirectionControl(
		GLFW_KEY_UP,
		GLFW_KEY_DOWN,
		GLFW_KEY_LEFT,
		GLFW_KEY_RIGHT,
		m_input
	));

	main_cam.append_controller("FourDirection", main_cam_controller);

	g_cams.push_back( Camera(vector3(0, 0, 40)) );

	g_cams[0].connect_entity(&main_cam);

	return true;
}
	
void System::shutdown() {
	bool result = true;

	if ( m_graphics != nullptr ) {
		result = m_graphics->shutdonw();
		if( !result ) {
			cout << "warning : fail to graphics shutdown" << endl;
		}

		delete m_graphics;
		m_graphics = nullptr;
	}

	/**
	 * @ TODO : Delete under the code line
	 * 			this code wrotten only for test
	 */

	if(main_cam_controller != nullptr) {
		main_cam_controller.reset();
	}
}

// ---------- System's setter 	--------------------------------------------------

void System::set_screen_size(int width, int height) {
	this->screen_width = width;
	this->screen_width = height;
}

// -------------------------------------------------------------------------------

void System::run() {
	int exit = 0;

	#ifdef __OPENGL__	
		m_graphics->clear_screen();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable ( GL_BLEND );
		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	#endif /* __OPENGL__ */
	
	do {
		/**
		 * @ TODO : Delete under the code line
		 * 			this code wrotten only for test
		 */
		main_cam_controller->update();
		main_cam.update();

		// ==================== until here ====================

		exit = m_graphics->render();

	} 	while ( ! exit );

	#ifdef __OPENGL__	
		glDisable ( GL_BLEND );
	#endif /* __OPENGL__ */
}

} // end of namespace : graphics
