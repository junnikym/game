#include <iostream>

#include "graphics/system.hpp"

using namespace std;

#ifdef __OPENGL__
	graphics::INPUT g_input_msger;
#endif /* __OPENGL__ */

int main() {
	bool result = false;
	graphics::SYSTEM system( "title", 800, 600);

#ifdef __OPENGL__
	g_input_msger.initialize();
#endif /* __OPENGL__ */

	result = system.initialize();
	if( ! result )
		return 1;

	system.run();

	system.shutdown();
	
	cout << "test success" << endl;

	return 0;
}