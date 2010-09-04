/*
 * Primitive.hh
 *
 *  Created on: 24-Jan-2009
 *      Author: will
 */

#ifndef PRIMITIVE_HH_
#define PRIMITIVE_HH_

#include "../Vector3f.hh"
#include "../Material.hh"

class Primitive
{
	public:
		enum Intersection {None, Hit, Inside};

		Primitive( Vector3f pos );

		void	 setPosition( Vector3f& pos);
		Vector3f getPosition();

		void	 setMaterial(const Material& mat);
		Material getMaterial();

		void	setLight(bool val);
		bool	isLight();

		virtual Intersection intersectsRay( Vector3f& origin,  Vector3f& direction, float& dist) = 0;

		virtual Vector3f getNormal(Vector3f& point) = 0;
		Vector3f getReflectionRay(Vector3f& intersectpoint, Vector3f& viewdir);

	private:
		Vector3f	position;
		Material	material;
		bool		light;
};

#endif /* PRIMITIVE_HH_ */
