/*
 * Plane.hh
 *
 *  Created on: 28-Jan-2009
 *      Author: will
 */

#ifndef PLANE_HH_
#define PLANE_HH_

#include "Primitive.hh"
#include "../Vector3f.hh"

class Plane : public Primitive
{
	public:
		Plane(const Vector3f& normal, const float& distance);
		Intersection intersectsRay( Vector3f& origin,  Vector3f& direction, float& dist);

		Vector3f getNormal(Vector3f& point);
	private:
		float		d;
		Vector3f	normal;
};


#endif /* PLANE_HH_ */
