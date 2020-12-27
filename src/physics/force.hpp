#ifndef FORCE_HPP
#define FORCE_HPP

#include "../math/vector.hpp"
#include "../integrate_types.hpp"
#include "../common.hpp"

namespace phy {

constexpr double FORCE_TIME_EPSILON = 0.001;

using namespace math;

/* --------------------------------------------------
 *	Force
 -------------------------------------------------- */

class Force {

	public:
		Force() = default;
		Force( const Vector<double>& vec, double speed = 1.0 );

		Vector<double> get();

		double get_delta_time();
		double get_last_time();

		virtual Vector<double> update();

		void set_vec(Vector<double> vec);
		void set_speed(double speed);

		void mul_vec(const double& x);

	protected:
		void initialize( const Vector<double>& vec, double&& speed );
		void update_timer();

		Vector<double> m_vec;
		double m_speed;

		double m_delta_t = 0.0;
		double m_last_t = 0.0;
};

/**
 * 	Accelator : 
 */

class Accelator : public Force {
	public:
		Accelator( const Vector<double>& vec, double speed = 1.0 );

		// @ Override
		Vector<double> update();
		
		void activate( bool act );
	
	private:
		double&& get_delta( const double& start_t, const double& end_t );
		//double backward_delta( const double& t, const double&  );
		//double get_speed_at( const double& t );

		bool m_activation_accel = true;

		double m_start_t = 0.0;
};

/**
 * 	P2P_Mover:
 * 		help that point to point move
 */

class P2P_Mover : public Force {
	public:
		P2P_Mover();

		// @ Override
		Vector<double> update();
};

} // end of namespace : phy

#endif	/* FORCE_HPP */