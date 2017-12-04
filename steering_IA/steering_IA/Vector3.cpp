#include "stdafx.h"
#include "Vector3.h"
float Vector3::magnitud()
{
	float f_mg = 0;
	for (int i = 0; i < 3; ++i)
		f_mg += pow(this->v[i], 2);
	f_mg = sqrt(f_mg);
	return f_mg;
}
Vector3 Vector3::normalized()
{
	Vector3 vc_normalized;
	float f_mag = this->magnitud();
	f_mag = 1 / f_mag;
	for (int i = 0; i < 3; ++i)
		vc_normalized.v[i] = this->v[i] * f_mag;
	return vc_normalized;
}
Vector3 Vector3::normalize()
{
	*this = normalized();
	return *this;
}
Vector3 Vector3::truncate(const float max)
{
	return (this->magnitud() > max ? this->normalized() * max : *(this));
}
Vector3 Vector3::operator*(Vector3 & vc_vector)
{
	Vector3 cv_product;
	for (int i = 0; i < 3; ++i)
		cv_product.v[i] = this->v[i] * vc_vector.v[i];
	return cv_product;
}
Vector3 Vector3::operator*(float f_escalar)
{
	Vector3 cv_product;
	for (int i = 0; i < 3; ++i)
		cv_product.v[i] = this->v[i] * f_escalar;
	return cv_product;
}
Vector3 Vector3::operator-(Vector3 & vc_vector)
{
	Vector3 cv_result;
	for (int i = 0; i < 3; i++)
		cv_result.v[i] = this->v[i] - cv_result.v[i];
	return cv_result;
}
Vector3 Vector3::operator+(Vector3 & vc_vector)
{
	Vector3 cv_result;
	for (int i = 0; i < 3; i++)
		cv_result.v[i] = this->v[i] + cv_result.v[i];
	return cv_result;
}
Vector3 Vector3::operator/(float f_escalar)
{
	return Vector3(this->x/f_escalar,this->y/f_escalar,this->z/f_escalar);
}
void Vector3::operator=(float f_unit)
{
	for (int i = 0; i < 3; i++)
		this->v[i] = f_unit;
}
float Vector3::rad2deg()
{
	if (this->x != 0 && this->y != 0)
		return(atan2f(this->y, this->x));
	return 0.0f;
}
float Vector3::deg2rad()
{
	if (this->x != 0.f && this->y != 0.f)
		return (atan2f(this->y, this->x)) * 180 / 3.141592;
	return 0.0f;
}
Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vector3::Vector3(float f_x, float f_y, float f_z)
{
	this->x = f_x;
	this->y = f_y;
	this->z = f_z;
}
Vector3::Vector3(float f_x, float f_y)
{
	this->x = f_x;
	this->y = f_y;
	this->z = 0;
}
Vector3::Vector3(float f_const)
{
	*(this) = f_const;
}
float Vector3::dot(Vector3&B) {
	return ((this->x*B.x) + (this->y*B.y) + (this->z*B.z));
}

Vector3::~Vector3()
{
}