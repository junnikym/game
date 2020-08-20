#include "system.hpp"

namespace graphics {

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
		exit = m_graphics->render();

	} 	while ( ! exit );

	#ifdef __OPENGL__	
		glDisable ( GL_BLEND );
	#endif /* __OPENGL__ */
}

} // end of namespace : graphics
