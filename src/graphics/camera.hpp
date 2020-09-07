#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../common.hpp"

#include "../physics/entity.hpp"

/* --------------------------------------------------
 * Default Cammera Setting Value
 -------------------------------------------------- */

#define __CAM_DEFAULT_YAW 			-90.0
#define __CAM_DEFAULT_PITCH 		 0.0
#define __CAM_DEFAULT_SPEED 		 2.5
#define __CAM_DEFAULT_SENSITIVITY 	 0.1
#define __CAM_DEFAULT_ZOOM 			 45.0

namespace graphics {

/****************************************************************************
 *	Mesh			| Class
 * 
 *  Manage vertices
 ****************************************************************************/

class Camera {
	public:
		Camera();
		Camera(vector3 pos);
		Camera(
			vector3 pos,
			vector3 look_at,
			double yaw, double pitch
		);

		void set_asix(double yaw, double pitch, double roll);
		void connect_entity(const phy::Entity* ent_ptr);
		void append_offset_axis(
			const double& yaw,
			const double& pitch, 
			const double& roll
		);

		void set_pos(double x, double y, double z);
		void append_offset_pos(
			const double& x,
			const double& y,
			const double& z
		);

		void intialize();

		void set_zoom();

		matrix4 get_view();
		double 	get_zoom();
		
	private:
		void update();

	private:
		vector3 position;
		vector3 world_up;

		/* 
		 *	yaw 	: axis.x
		 *	pitch 	: axis.y
		 *	roll 	: axis.z
		 */
		vector3 axis;

		vector3 front;
		vector3 right;
		vector3 up;
		
		double zoom;

		const phy::Entity* m_entity = nullptr;
};


} // end of namespace : graphics

#endif /* ! CAMERA_HPP */