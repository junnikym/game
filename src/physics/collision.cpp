#include "collision.hpp"

namespace phy {

// CollisionIndicator CollisionDetector_AABB::detect( const MathVecList<double>& lhs, 
// 												   double& lhs_angle, 
// 												   Vector<double>& lhs_pos,
// 												   const MathVecList<double>& rhs, 
// 												   Vector<double>& rhs_pos,
// 												   double& rhs_angle ) {
// 	CollisionIndicator result;

// 	return result;
// }

typedef struct {
	double min;
	double max;
	std::vector<double> dots;
} PROJECTION;

CollisionIndicator CollisionDetector_SAT::detect( 
	const Shape& lhs, const Vector<double>& lhs_pos, const double& lhs_angle,
	const Shape& rhs, const Vector<double>& rhs_pos, const double& rhs_angle
) {
	CollisionIndicator result;

	// 1. Get all axis of shapes
	//--------------------------------------------------
	MathVecList<double> axes;

	auto get_axis = [&axes](const Shape& shape) {
		const MathVecList<double>* verties = shape.get_verties();
		int length = verties->size();

		for(int i = 0; i < length; i++) {
			math::Vector<double> normalized = 
				(*verties)[i] - (*verties)[ ((i+1 < length) ? i+1 : 0) ];
			
			normalized.normalize();

			axes.push_back(normalized);
		}
	};
	
	get_axis(lhs);
	get_axis(rhs);

	// 2. Project point to axis
	//--------------------------------------------------
	auto project = [] ( const Shape& shape,
						const math::Vector<double>& pos, 
						const math::Vector<double>& axis ) {
		
		PROJECTION result = {0, 0, };
		double comp_dot = 0;
		const MathVecList<double>* points = shape.get_verties();

		result.max = Vector<double>::dot(axis, (*points)[0]);
		result.min = result.max;

		for(int i = 1; i < points->size(); i++) {
			comp_dot = Vector<double>::dot(axis, (*points)[i]);
			
			if (comp_dot < result.min) 
				result.min = comp_dot;
			else if (comp_dot > result.max)
				result.max = comp_dot;

			result.dots.push_back(comp_dot);
		}

		return result;
	};

	double min_overlap = std::numeric_limits<double>::min();

	for(auto it : axes) {
		auto lhs_proj = project(lhs, lhs_pos, it);
		auto rhs_proj = project(rhs, rhs_pos, it);

		std::cout << "lhs : ( " << 
			lhs_proj.min << ", " << lhs_proj.max << " ) // " <<
			"rhs : ( " << 
			rhs_proj.min << ", " << rhs_proj.max << " ) " << std::endl;

		if (lhs_proj.min <= rhs_proj.max & lhs_proj.max >= rhs_proj.min) {
			auto overlap = std::min( 
								rhs_proj.max - lhs_proj.min, 
								lhs_proj.max - rhs_proj.min 
							);

			if (overlap < min_overlap) {
				min_overlap = overlap;
				result.MTV = it;
			}
		}
		else {
			result.state = COLLISION_NOT_DETECTED;
			return result;
		}
	}

	result.MTV *= min_overlap;
	return result;
}

} // end of namespace : phy