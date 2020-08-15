#ifndef MOVER_HPP
#define MOVER_HPP

#include "control.hpp"

namespace input { 

class Mover {
	public:
		Mover();

		// Append binary control class to Mover
		append(
			const int& positive_key, 
			const int& negative_key, 
			const int& strength
		);
		
	private:
		Control* controller[512];
};

} // end of namespace : input

#endif	/* ! MOVER_HPP */