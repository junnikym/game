#ifndef FRICTION_HPP
#define FRICTION_HPP

#include "entity.hpp"
#include "PhyBox.hpp"

namespace phy {

class Friction {
	public:
		Friction(double constant);

		/**
		 * 	set collision box 
		 * 		-> reference box, activation friction only in the box
		 */

		void apply(Entity);

	private:
		PhyBox apply_range;
};

} // end of namespace : phy

#endif