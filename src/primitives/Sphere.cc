/*
 * Sphere.cc
 *
 *  Created on: 24-Jan-2009
 *      Author: will
 */

#include "Sphere.hh"
#include "../Matrix44f.hh"
#include <cmath>

Sphere::Sphere(const Vector3f& origin,  float radius) : Primitive(origin)
{
	this->radius = radius;
}

Vector3f Sphere::getNormal(Vector3f& point)
{
	return (point - this->getPosition()) * this->radius;
}

float Sphere::getRadius() {
	return this->radius;
}
void Sphere::setRadius(float radius) {
	this->radius = radius;
}

bool Sphere::contains(Vector3f& point)
{
	return (point - this->getPosition()).length() <= this->radius;
}

// from http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection
// adapted for this project
Primitive::Intersection Sphere::intersectsRay( Vector3f& origin,  Vector3f& direction, float& dist)
{
	if(this->contains(origin))
		return Primitive::Inside;

	Vector3f o = origin - this->getPosition();

	// Calculate the discriminant (b^2 - 4ac)
	float a = direction.dotproduct(direction);
	float b = 2 * direction.dotproduct(o);
	float c = o.dotproduct(o) - (this->radius * this->radius);

	float dis = b*b - 4*a*c;

	// guard against imaginary numbers
	if(dis <= 0)
		return Primitive::None;

	// calculate the q term
	dis = sqrtf(dis);
    float q;
    if (b < 0)
        q = (-b - dis)/2.0;
    else
        q = (-b + dis)/2.0;

    // compute t1 and t2
    float t1 = q / a;
    float t2 = c / q;

	// make sure the two terms are in order of ascending distance (swap if necessary)
	if( t2 < t1 ) {
		float temp = t1;
		t1 = t2;
		t2 = temp;
	}

	// if the farther intersection is negative then the sphere is not intersected at all
	if( t2 < 0 )
		return Primitive::None;

	// at this point we are certain t2 is positive or zero
	// therefore if t1 is negative the closest intersection is t2, otherwise it is t1
	dist = (t1 < 0)?t2:t1;

	return Primitive::Hit;
}

vector<Vector3f> Sphere::getShadowPoints(Vector3f& origin, Vector3f& direction, unsigned int n) {
	vector<Vector3f> result;

	// We want the plane to bisect the sphere and only produce shadow points on the resulting hemisphere

	// Calculate the plane's normal
	Vector3f pnormal = -direction;

	// This algorithm will produce a set of points relative to the vector <0,1,0>
	Vector3f ptnorm(0.0f, 1.0f, 0.0f);

	// Find the X,Y,Z components of the angles between these two vectors

	// Calculate the rotation matrix for the points
	Matrix44f rot = Matrix44f::RotationMatrix(0.0f, 0.0f, M_PI);

	// Add the poles to the result since they'd normally be added multiple times
	Vector3f npole(0.0f, 0.0f,  this->radius);
	Vector3f spole(0.0f, 0.0f, -this->radius);

	result.push_back( (rot * npole) + this->getPosition() );
	result.push_back( (rot * spole) + this->getPosition() );

	// Calculate the maximum number of points we can evenly distribute
	n = (int)sqrt(n-2);

	// We will use increments along the x axis and angles between the point vectors, calculate them
	float dx = (2.0f * this->radius) / (float)(n-1);
	float dO = M_PI / (float)(n-1);

	// Create points on the equator
	for(unsigned int i = 0; i < n; i++) {
		float x = this->radius - (dx * i);
		float y = this->radius * sin(dO * i);

		// Create a vector at this point and add it to the result
		Vector3f horiz(x, y, 0.0f);
		result.push_back( (rot * horiz) + this->getPosition() );

		// At this point calculate points along the line of longitude, be sure to skip the poles
		// At each point we can add <x,y,+z> and <x,y,-z> so only calculate half the number of points
		int half_n = (int)((float)n / 2.0f) + 1;

		for(int j = 1; j < half_n; j++) {
			// Calculate the percentage along the vector V we want this point to be at
			float scale = (2.0f * j) / (float)n;

			// Calculate the Z value of this point
			float z = this->radius * sin( dO * (half_n - j) );

			// Add the <x,y,+z> and <x,y,-z> vectors to the result
			Vector3f plusz (x * scale, y * scale,  z);
			Vector3f minusz(x * scale, y * scale, -z);

			result.push_back( (rot * plusz)  + this->getPosition() );
			result.push_back( (rot * minusz) + this->getPosition() );
		}

	}

	return result;
}
