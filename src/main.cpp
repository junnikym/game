
#include <iostream>

#include "graphics/system.hpp"

using namespace std;

int main() {
	bool result = false;
	graphics::System system( "title", 800, 600);

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