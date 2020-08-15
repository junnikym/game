#include "camera.hpp"

namespace graphics {

Camera::Camera() {
	intialize();

	update();
}

Camera::Camera(vector3 pos) {
	intialize();

	this->position = move(pos);

	update();
}

Camera::Camera(
	vector3 pos,
	vector3 up,
	double yaw, double pitch
) {
	intialize();

	this->position 	= move(pos);
	this->world_up 	= move(up);
	
	this->axis.x = yaw;
	this->axis.y = pitch;

	update();
}

void Camera::intialize() {
	this->position 	= vector3(0.0f, 0.0f, 0.0f);
	this->up 		= vector3(0.0f, 1.0f, 0.0f);
	this->world_up =  this->up;

	this->axis[0] 	= __CAM_DEFAULT_YAW;
	this->axis[1] 	= __CAM_DEFAULT_PITCH;
	this->axis[2] 	= 0;

	this->zoom = __CAM_DEFAULT_ZOOM;

	this->front = vector3(0.0, 0.0, -1.0);
}

void Camera::set_asix(double yaw, double pitch, double roll) {
	this->axis.x = move(yaw);
	this->axis.y = move(pitch);
	this->axis.z = move(roll);

	update();
}

void Camera::append_offset_axis(
	const double& yaw,
	const double& pitch,
	const double& roll
) {
	this->axis.x += yaw;
	this->axis.y += pitch;
	this->axis.z += roll;

	update();
}

void Camera::set_pos(double x, double y, double z) {
	this->position.x = move(x);
	this->position.y = move(y);
	this->position.z = move(z);

	update();
}

void Camera::append_offset_pos(
	const double& x,
	const double& y,
	const double& z
) {
	this->position.x += x;
	this->position.y += y;
	this->position.z += z;

	update();
}

matrix4 Camera::get_view() {
	#if defined(__OPENGL__)
		return glm::lookAt(position, position + front, up);
	#elif defined(__DX__)
		// @ TODO : Implement
	#endif
}

double Camera::get_zoom() {
	return this->zoom;
}

void Camera::update() {
	/* --------------------------------------------------
	 * x asix : cos( yaw ) * cos ( pitch )
	 * y asix : sin( pitch )
	 * z asix : sin( yaw ) * cos ( pitch )
	 -------------------------------------------------- */
	front.x = cos( radians(axis.x) ) * cos( radians(axis.y) );
	front.y = sin( radians(axis.y) );
	front.z = sin( radians(axis.x) ) * cos( radians(axis.y) );

	this->front = normalize(this->front);
	this->right = normalize( cross(front, world_up) );
	this->up 	= normalize( cross(right, front) );
}


} // end of namespace : graphics