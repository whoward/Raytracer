/*
 * BasicSceneManager.cc
 *
 *  Created on: 28-Jan-2009
 *      Author: will
 */

#include "BasicSceneManager.hh"
#include <cmath>
#include <iostream>

BasicSceneManager::BasicSceneManager( const Vector3f& eyepos, const Vector3f& eyetarget)
	: SceneManager(eyepos, eyetarget)
{

}

void BasicSceneManager::addPrimitive( Primitive* prim) {
	this->scene.push_back(prim);
}

int BasicSceneManager::primitiveCount() {
	return this->scene.size();
}

void BasicSceneManager::update(long time) {
	//TODO:
}

SceneManager::Intersect* BasicSceneManager::raytrace( Vector3f& point,  Vector3f& direction) {
	float 					lowestdist	= this->getRaytraceDistance();
	Primitive* 				nearest		= 0;
	Primitive::Intersection type		= Primitive::None;

	for(unsigned int i = 0; i < scene.size(); i++) {
		float distance;
		Primitive::Intersection result = scene[i]->intersectsRay(point, direction, distance);

		if(result != Primitive::None && (distance < lowestdist || lowestdist < 0)) {
			nearest = scene[i];
			lowestdist = distance;
			type = result;
		}
	}

	if(nearest == 0)
		return 0;

	// calculate the intersection point
	Vector3f intersection = point + (direction * lowestdist);

	return new SceneManager::Intersect(nearest, intersection, lowestdist, type);
}

Vector3f BasicSceneManager::raycolour( Vector3f& point,  Vector3f& direction, int bouncelimit ) {
	// Check if we've hit the bounce limit for this ray, if so just return a colour that wont modify the result
	if(bouncelimit-- == 0) {
		return Vector3f(0.0f, 0.0f, 0.0f);
	}

	// Raytrace down the defined ray
	SceneManager::Intersect* intersection = raytrace(point, direction);

	// If there was no intersection just return the background colour
	if(intersection == 0)
		return this->getBackgroundColor();

	// Pull out the intersected object since it will be referred to often;
	Primitive* intersected = intersection->intersected;

	// Since we'll continually refer to it, assign the material to a variable
	Material pointMat = intersected->getMaterial();

	// If the intersection was inside return the object's colour
	if(intersection->type == Primitive::Inside)
		return pointMat.getColour();

	// Assume no lighting is to be calculated for lights, so just return its colour
	if(intersected->isLight() == true)
		return pointMat.getColour();

	// Get the ambient colour of this point
	Vector3f color = pointMat.getColour() * pointMat.getAmbient();

	// Calculate the normal vector at the intersection point
	Vector3f normalvec = intersected->getNormal(intersection->point);

	// If the material is reflective bounce out a ray for reflection and add it to the ambient colour
	if(pointMat.getReflection() > 0.0f) {
		float reflection = pointMat.getReflection();

		// Calculate the ray of reflection
		Vector3f r = intersected->getReflectionRay(intersection->point, direction);

		// Determine an epsilon point along this ray of reflection
		Vector3f repsilon = intersection->point + (r.normalize() * 0.001);

		// Add the colour of reflection to the current colour
		color = color + this->raycolour(repsilon, r, bouncelimit) * reflection;
	}

	// Go through every light, see if it can be traced to and add colour due to their effects
	for(unsigned int i = 0; i < scene.size(); i++) {
		// For convenience get the current light
		Primitive* light = scene[i];

		// Calculate the light vector
		Vector3f lightvec = light->getPosition() - intersection->point;

		// Calculate a small epsilon point in the direction of the light that is slightly off the intersect point
		Vector3f epsilon = intersection->point + lightvec.normalize();

		// Raytrace from the epsilon for this point to the light
		SceneManager::Intersect* result	= raytrace(epsilon, lightvec);

		// If there was no intersection, or it intersected another object then it is in shadow
		if(result == 0 || result->intersected != light)
			continue;

		// If diffuse lighting is to be used calculate it and add it
		if(pointMat.getDiffuse() > 0.0f) {
			float dot = normalvec.dotproduct(lightvec);
			if(dot > 0) {
				float diff = dot * pointMat.getDiffuse();
				color = color + (pointMat.getColour() * light->getMaterial().getColour()) * diff;
			}
		}

		// If specular lighting is to be used calculate it and add it
		if(pointMat.getSpecular() > 0.0f) {
			float shininess = pointMat.getPhongExponent();
			float specular = pointMat.getSpecular();

			Vector3f el = -direction + lightvec;
			Vector3f h = el * (1.0f/el.length());
			float hn = h.dotproduct(normalvec);

			color = color + (light->getMaterial().getColour() * pow(hn,shininess)) * specular;
		}
	}

	return color;
}

Vector3f BasicSceneManager::raycolour( Vector3f& point,  Vector3f& direction ) {
	return this->raycolour(point, direction, this->getRaytraceDepth());
}
