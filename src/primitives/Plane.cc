/*
 * Sphere.cc
 *
 *  Created on: 24-Jan-2009
 *      Author: will
 */

#include "Plane.hh"
#include <cmath>

Plane::Plane(const Vector3f& normal, const float& distance) : Primitive(normal * distance)
{
	this->normal = normal;
	this->d = distance;
}

Vector3f Plane::getNormal(Vector3f& point)
{
	return this->normal;
}

Primitive::Intersection Plane::intersectsRay( Vector3f& origin,  Vector3f& direction, float& dist)
{
	float theta = normal.dotproduct(direction);

	// if the angle is 0 degrees this means that the ray and plane are parallel and will never intersect
	if(theta == 0.0f) {
		dist = 0.0f;
		return Primitive::None;
	}

	// calculate the distance
	dist = -(origin.dotproduct(normal) + this->d) / theta;

	// dist should only be equal to zero if it is on the plane
	if(dist > 0)
		return Primitive::Hit;
	else
		return Primitive::None;
}
