	#pragma once
#include <math.h>
class Vector3
{
public:
	union {
		struct {
			float x, y, z;
		};
		float v[3];
	};
	float  magnitud();
	Vector3 normalized();
	Vector3	normalize();
	Vector3 truncate(const float max);
	Vector3 operator*(Vector3& vc_vector);
	Vector3 operator*(float f_escalar);
	Vector3 operator-(Vector3& vc_vector);
	Vector3 operator+(Vector3& vc_vector);
	Vector3 operator/(float f_escalar);
	float dot( Vector3&B);
	void  operator=(float f_unit);
	float		rad2deg();
	float		deg2rad();
	Vector3();
	Vector3(float f_x, float f_y, float f_z);
	Vector3(float f_x, float f_y);
	Vector3(float f_const);
	~Vector3();
};