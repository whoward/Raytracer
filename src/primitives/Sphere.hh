/*
 * Sphere.hh
 *
 *  Created on: 23-Jan-2009
 *      Author: will
 */

#ifndef SPHERE_HH_
#define SPHERE_HH_

#include "Primitive.hh"
#include "../Vector3f.hh"

#include <vector>

class Sphere : public Primitive
{
	public:
		Sphere(const Vector3f& origin,  float radius);
		Primitive::Intersection intersectsRay( Vector3f& origin,  Vector3f& direction, float& dist);

		Vector3f getNormal(Vector3f& point);
		bool contains(Vector3f& point);

		float getRadius();
		void setRadius(float radius);

		vector<Vector3f> getShadowPoints(Vector3f& origin, Vector3f& direction, unsigned int n);

	private:
		float radius;
};

#endif /* SPHERE_HH_ */
