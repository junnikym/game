#ifndef PHY_BOX_HPP
#define PHY_BOX_HPP

#include "../common.hpp"

namespace phy {

/**
 * The Container for physical coverage
 */
class PhyContainer {
	private:
		std::vector<Shape> shapes;
		
	public:
		PhyBox();
};

} // end of namespace : phy

#endif	// end of PHY_BOX_HPP