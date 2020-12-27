
#include <iostream>

//#include "graphics/system.hpp"
#include "./physics/shape.hpp"
#include "./physics/collision.hpp"

using namespace std;

int main() {
//	bool result = false;
//	graphics::System system( "title", 800, 600);

// #ifdef __OPENGL__
// 	// @TODO : need to modify
// 	g_input_msger.initialize(0, 0);
// #endif /* __OPENGL__ */

// 	result = system.initialize();
// 	if( ! result )
// 		return 1;

// 	system.run();

// 	system.shutdown(); 

	phy::Shape triangle_mather{{-1, -1}, {0, 1}, {1, -1}};
	phy::Shape polygon_mather{{0, 1}, {1, 0.3}, {0.6, -1}, {-0.6, -1}, {-1, 0.3}};

	math::Vector<double> triangle_pos {2, 2};
	math::Vector<double> polygon_pos {2, 2};

	double triangle_angle = 20.0;
	double polygon_angle = 0.0;

	phy::Shape triangle = triangle_mather.ratation(triangle_angle);
	phy::Shape polygon = polygon_mather.ratation(polygon_angle);

	int count = 0;
	auto vec = triangle.get_verties();

	cout << "triangle : " << endl;
	for(auto it : *vec) {
		cout << "\t" << count << " : " << " ( ";

		for(int i = 0; i < it.size(); i++)
			cout << it[i] << ", ";

		cout << " ) " << endl;
	}

	count = 0;
	vec = polygon.get_verties();

	cout << "polygon : " << endl;
	for(auto it : *vec) {
		cout << "\t" << count << " : " << " ( ";

		for(int i = 0; i < it.size(); i++)
			cout << it[i] << ", ";

		cout << " ) " << endl;
	}
	cout << " )" << endl;

	phy::CollisionDetector* detector = new phy::CollisionDetector_SAT();
	auto result = detector->detect(
		*triangle.get_verties(), triangle_pos, triangle_angle,
		*polygon.get_verties(), polygon_pos, polygon_angle
	); 

	// cout << "state : " << result.state <<endl;
	
	cout << "test success" << endl;

	//delete detector;

	return 0;
}