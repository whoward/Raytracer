/*
 * SceneManager.hh
 *
 *  Created on: 28-Jan-2009
 *      Author: will
 */

#ifndef SCENEMANAGER_HH_
#define SCENEMANAGER_HH_

#include "../primitives/Primitive.hh"

class SceneManager
{
	public:
		class Intersect {
			public:
				Intersect(Primitive* i, Vector3f point, float dist, Primitive::Intersection type);
				Primitive*	intersected;
				Vector3f	point;
				float		distance;
				Primitive::Intersection type;
		};

		SceneManager( const Vector3f& eyepos, const Vector3f& eyetarget);
		virtual ~SceneManager();

		virtual void addPrimitive( Primitive* prim) = 0;
		//TODO: addEntity()
		virtual int primitiveCount() = 0;

		Vector3f getEyePosition();
		void setEyePosition( Vector3f& position);

		Vector3f getEyeTarget();
		void setEyeTarget( Vector3f& target);

		Vector3f getEyeDirection();

		virtual void update(long time) = 0;

		void setBackgroundColor( Vector3f& color);
		Vector3f& getBackgroundColor();

		virtual SceneManager::Intersect* raytrace( Vector3f& point,  Vector3f& direction) = 0;
		virtual Vector3f raycolour( Vector3f& point,  Vector3f& direction) = 0;

		void setRaytraceDistance(float dist);
		float getRaytraceDistance();

		void setRaytraceDepth(int depth);
		int getRaytraceDepth();

		void setDiffuseEnabled(int enabled);
		int getDiffuseEnabled();

		void setSpecularEnabled(int enabled);
		int getSpecularEnabled();

		void setReflectionEnabled(int enabled);
		int getReflectionEnabled();

		void setAmbientEnabled(int enabled);
		int getAmbientEnabled();

	private:
		Vector3f	eyepos;
		Vector3f	eyetarget;
		Vector3f	bgcolor;

		float		rtdist;
		int			rtdepth;

		int specularEnabled;
		int diffuseEnabled;
		int reflectionEnabled;
		int ambientEnabled;
};


#endif /* SCENEMANAGER_HH_ */
