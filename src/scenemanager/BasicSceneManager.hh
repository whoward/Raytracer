/*
 * BasicSceneManager.hh
 *
 *  Created on: 28-Jan-2009
 *      Author: will
 */

#ifndef BASICSCENEMANAGER_HH_
#define BASICSCENEMANAGER_HH_

#include "SceneManager.hh"
#include <vector>

class BasicSceneManager : public SceneManager
{
	public:
		BasicSceneManager(const Vector3f& eyepos, const Vector3f& eyetarget);

		void addPrimitive( Primitive* prim);
		int primitiveCount();

		void update(long time);

		SceneManager::Intersect* raytrace( Vector3f& point,  Vector3f& direction);
		Vector3f raycolour( Vector3f& point,  Vector3f& direction);

	private:
		Vector3f raycolour( Vector3f& point,  Vector3f& direction, int bouncelimit );

		vector<Primitive*> scene;

};

#endif /* BASICSCENEMANAGER_HH_ */
