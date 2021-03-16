#include "force.hpp"

namespace phy {

/* --------------------------------------------------
 *	Force
 -------------------------------------------------- */

Force::Force( const Vector<double>& vec, double speed ) {
	initialize( vec, std::move(speed) );
}

void Force::initialize( const Vector<double>& vec, double&& speed ) {
	m_delta_t = _get_time();
	
	set_speed( std::move(speed) );
	set_vec( vec );
}

double Force::get_delta_time() {
	return m_delta_t;
}

double Force::get_last_time() {
	return m_last_t;
}

Vector<double> Force::get() {
	return m_vec;
}

Vector<double> Force::update() {
	update_timer();

	return m_vec * ( m_delta_t * m_speed );
}

void Force::set_vec(Vector<double> vec) {
	m_vec = std::move( vec );
	m_vec.normalize();
}

void Force::set_speed(double speed) {
	m_speed = std::move(speed);
}

void Force::update_timer() {
	auto current_t = _get_time();
	m_delta_t = m_last_t - current_t;
	m_last_t = std::move(current_t);
}

void Force::mul_vec(const double& x) {
	m_vec *= x;
}

/* --------------------------------------------------
 *	Accelator
 -------------------------------------------------- */

Accelator::Accelator( const Vector<double>& vec, double speed ) {
	initialize( vec, std::move(speed) );
	m_start_t = _get_time();
}

Vector<double> Accelator::update() {
	update_timer();

	if(m_activation_accel) {
		auto begin_t = m_start_t - m_last_t;
		double accel_speed = get_delta( begin_t, begin_t + m_delta_t );
		
		return m_vec * accel_speed;
	}

	return m_vec;
}

void Accelator::activate( bool act ) {
	m_activation_accel = true;
}

double&& Accelator::get_delta( const double& start_t, const double& end_t ) {

	/**
	 *	Delta Vector = ∫ ( a * t ) dt
	 *			F(x) => 0.5 * a * t^2
	*/

	double result = m_speed * 0.5 * Square(end_t);
	result -= m_speed * 0.5 * Square(start_t);

	return std::move(result);
}

// double Accelator::backward_delta( const double& t ) {
// 	/**
// 	 * 	( a * t ) = accel
// 	 * 	  => accel / a = t
// 	 */

	

// 	return 0.0;
// }

// double Accelator::get_speed_at( const double& t ) {
// 	return 0.0;
// }

} // end of namespace : phy