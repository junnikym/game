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
	
	// -- m_graphics init 	----------------------------------------------

	m_graphics = new Graphics;
	if(m_graphics == nullptr) 
		return false;

	result = m_graphics->initialize( screen_width, screen_height, m_app_title );	
	if( ! result ) 
		return false;

	// -------------------------------------------------------------------//

	// -- input init 		----------------------------------------------

#ifdef __OPENGL__
	m_input = &g_input_msger;
#else
	m_input = new Input;
	if(m_input == nullptr) 
		return false;
#endif /* __OPENGL, else */

	// -------------------------------------------------------------------//

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

		glEnable(GL_DEPTH_TEST);	// 화면의 깊이값을 측정하여 프레그먼트를 사용할지
		glDepthFunc(GL_LESS);		// 폐기할지 지정한다.

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
