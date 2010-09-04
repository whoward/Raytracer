/*
 * Vector3f.cc
 *
 *  Created on: 24-Jan-2009
 *      Author: will
 */
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "Vector3f.hh"

using namespace std;

Vector3f::Vector3f() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3f::Vector3f(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f Vector3f::operator=(const Vector3f* rhs) {
	if(this == rhs)
		return *this;

	this->x = rhs->x;
	this->y = rhs->y;
	this->z = rhs->z;

	return *this;
}

Vector3f Vector3f::operator=(const Vector3f& rhs) {
	if(this == &rhs)
		return *this;

	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;

	return *this;
}

void Vector3f::operator+=(const Vector3f& rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
}
void Vector3f::operator+=(const Vector3f* rhs) {
	this->x += rhs->x;
	this->y += rhs->y;
	this->z += rhs->z;
}
void Vector3f::operator-=(const Vector3f& rhs) {
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
}
void Vector3f::operator-=(const Vector3f* rhs) {
	this->x -= rhs->x;
	this->y -= rhs->y;
	this->z -= rhs->z;
}
void Vector3f::operator*=(const Vector3f& rhs) {
	this->x *= rhs.x;
	this->y *= rhs.y;
	this->z *= rhs.z;
}
void Vector3f::operator*=(const Vector3f* rhs) {
	this->x *= rhs->x;
	this->y *= rhs->y;
	this->z *= rhs->z;
}
void Vector3f::operator*=(float rhs) {
	this->x *= rhs;
	this->y *= rhs;
	this->z *= rhs;
}

Vector3f Vector3f::operator-() {
	return Vector3f(-x, -y, -z);
}
Vector3f operator+( const Vector3f& v1, const Vector3f& v2 ) {
	return Vector3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
Vector3f operator-( const Vector3f& v1, const Vector3f& v2 ) {
	return Vector3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
Vector3f operator+( const Vector3f& v1, const Vector3f* v2 ) {
	return Vector3f(v1.x + v2->x, v1.y + v2->y, v1.z + v2->z);
}
Vector3f operator-( const Vector3f& v1, const Vector3f* v2 ) {
	return Vector3f(v1.x - v2->x, v1.y - v2->y, v1.z - v2->z);
}
Vector3f operator*( const Vector3f& v1, const Vector3f& v2 ) {
	return Vector3f(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
Vector3f operator*( const Vector3f& v1, const Vector3f* v2 ) {
	return Vector3f(v1.x * v2->x, v1.y * v2->y, v1.z * v2->z);
}
Vector3f operator*( const Vector3f& v1, float f ) {
	return Vector3f(v1.x * f, v1.y * f, v1.z * f);
}
Vector3f operator*( float f, const Vector3f& v1 ) {
	return Vector3f(v1.x * f, v1.y * f, v1.z * f);
}

Vector3f operator^(const Vector3f& v1, const Vector3f& v2) {
	float x = v1.y * v2.z - v1.z * v2.y;
	float y = v1.z * v2.x - v1.x * v2.z;
	float z = v1.x * v2.y - v1.y * v2.x;

	return Vector3f(x,y,z);
}

Vector3f operator^(const Vector3f& v1, const Vector3f* v2) {
	float x = v1.y * v2->z - v1.z * v2->y;
	float y = v1.z * v2->x - v1.x * v2->z;
	float z = v1.x * v2->y - v1.y * v2->x;

	return Vector3f(x,y,z);
}

const bool Vector3f::operator==(const Vector3f& rhs) {
	return x == rhs.x && y == rhs.y && z == rhs.z;
}

const bool Vector3f::operator!=(const Vector3f& rhs) {
	return x != rhs.x || y != rhs.y || z != rhs.z;
}

Vector3f Vector3f::normalize() {
	Vector3f result = *this;
	float length = result.length();
	if(length > 1.0f) {
		result.x /= length;
		result.y /= length;
		result.z /= length;
	}
	return result;
}

const float Vector3f::dotproduct(const Vector3f& rhs) {
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

const float Vector3f::length() {
	return sqrt(x*x + y*y + z*z);
}

const string Vector3f::toString() {
	ostringstream s;
	s << setprecision(2) << fixed;
	s << "[ " << setw(10) << x << "," << setw(10) << y << "," << setw(10) << z << " ]";
	return s.str();
}
