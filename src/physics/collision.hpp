#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "../common.hpp"
#include "../math/vector.hpp"
#include "./shape.hpp"

#define COLLISION_DETECTED 1
#define COLLISION_NOT_DETECTED 0
#define COLLISION_ERROR -1

namespace phy {

using namespace math;

typedef struct {
	int state = COLLISION_DETECTED;
	math::Vector<double> MTV;	// Minimum Translation Vector
} CollisionIndicator;

class CollisionDetector {
	public:
		CollisionDetector() = default;

		virtual CollisionIndicator detect( 
			const Shape& lhs, const Vector<double>& lhs_pos, const double& lhs_angle, 
			const Shape& rhs, const Vector<double>& rhs_pos, const double& rhs_angle
		) = 0;

	private:
		static constexpr int priority = 100;
};

// class CollisionDetector_AABB : public CollisionDetector {
// 	public:
// 		CollisionIndicator detect( const MathVecList<double>& lhs, Vector<double>& lhs_pos, double& lhs_angle, 
// 								   const MathVecList<double>& rhs, Vector<double>& rhs_pos, double& rhs_angle ) override;

// 	private: static constexpr int priority = 23;
// };

/*

var project = function (worldPoints, axisVector) {

			var projection = { min : 0, max : 0, results : [] };

			projection.max = axisVector.dot(worldPoints[0]);
			projection.min = projection.max;

			worldPoints.forEach((point) => {

				var p = axisVector.dot(point);

				if (p < projection.min) {
					projection.min = p;
				} else if (p > projection.max) {
					projection.max = p;
				}

				projection.results.push(p);
			});

			return projection;
		};


*/

class CollisionDetector_SAT : public CollisionDetector {
	public:
		CollisionIndicator detect ( 
			const Shape& lhs, const Vector<double>& lhs_pos, const double& lhs_angle,
			const Shape& rhs, const Vector<double>& rhs_pos, const double& rhs_angle
		) override;

	private: static constexpr int priority = 21;
};

// class CollisionDetector_OBB : public CollisionDetector_SAT {
// 	public:
// 		CollisionIndicator detect( const MathVecList<double>& lhs, Vector<double>& lhs_pos, double& lhs_angle, 
// 								   const MathVecList<double>& rhs, Vector<double>& rhs_pos, double& rhs_angle ) override;

// 	private: static constexpr int priority = 22;
// };

// class CollisionDetector_Circle : public CollisionDetector {
// 	public:
// 		CollisionIndicator detect( const MathVecList<double>& lhs, Vector<double>& lhs_pos, double& lhs_angle, 
// 								   const MathVecList<double>& rhs, Vector<double>& rhs_pos, double& rhs_angle ) override;

// 	private: static constexpr int priority = 10;
// };

} // end of namespace : phy

#endif