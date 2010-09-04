/*
 * Material.hh
 *
 *  Created on: 23-Jan-2009
 *      Author: will
 */

#ifndef MATERIAL_HH_
#define MATERIAL_HH_

#include "Vector3f.hh"

class Material
{
	public:
		Material();
		Material(const Vector3f& color, const float& diffuse, const float& reflection, const float& ambience, const float& phong);

		void	 setColour( Vector3f& color);
		Vector3f getColour();

		void	 setAmbient( float& ambient);
		float	 getAmbient();

		void 	 setDiffuse( float& diffuse);
		float	 getDiffuse();

		void	 setReflection( float& reflection);
		float	 getReflection();

		float	 getSpecular();

		void	 setPhongExponent( float& phong);
		float	 getPhongExponent();

	private:
		Vector3f colour;
		float	 ambient;
		float	 reflection;
		float	 diffuse;
		float	 phong;
};

#endif /* MATERIAL_HH_ */
