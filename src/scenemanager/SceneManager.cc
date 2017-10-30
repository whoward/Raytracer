/*
 * SceneManager.cc
 *
 *  Created on: 28-Jan-2009
 *      Author: will
 */
#include "SceneManager.hh"

SceneManager::Intersect::Intersect(Primitive* i, Vector3f point, float dist, Primitive::Intersection type) {
	this->intersected = i;
	this->point = point;
	this->distance = dist;
	this->type = type;
}

SceneManager::SceneManager( const Vector3f& eyepos, const Vector3f& eyetarget) {
	this->eyepos = eyepos;
	this->eyetarget = eyetarget;
	this->rtdepth = -1;
	this->rtdist = -1;
	this->ambientEnabled = 1;
	this->specularEnabled = 1;
	this->diffuseEnabled = 1;
	this->reflectionEnabled = 1;
}

SceneManager::~SceneManager() {
	// Do Nothing
}

 Vector3f SceneManager::getEyePosition() {
	return this->eyepos;
}
void SceneManager::setEyePosition( Vector3f& position) {
	this->eyepos = position;
}

 Vector3f SceneManager::getEyeTarget() {
	return this->eyetarget;
}
void SceneManager::setEyeTarget( Vector3f& target) {
	this->eyetarget = target;
}

 Vector3f SceneManager::getEyeDirection() {
	return (this->eyetarget - this->eyepos).normalize();
}

void SceneManager::setBackgroundColor( Vector3f& color) {
	this->bgcolor = color;
}

 Vector3f& SceneManager::getBackgroundColor() {
	return this->bgcolor;
}

void SceneManager::setRaytraceDistance(float dist) {
	this->rtdist = dist;
}
 float SceneManager::getRaytraceDistance() {
	return this->rtdist;
}

void SceneManager::setRaytraceDepth(int depth) {
	this->rtdepth = depth;
}
 int SceneManager::getRaytraceDepth() {
	return this->rtdepth;
}

void SceneManager::setDiffuseEnabled(int enabled) {
	this->diffuseEnabled = enabled;
}

int SceneManager::getDiffuseEnabled() {
	return this->diffuseEnabled;
}

void SceneManager::setSpecularEnabled(int enabled) {
	this->specularEnabled = enabled;
}

int SceneManager::getSpecularEnabled() {
	return this->specularEnabled;
}

void SceneManager::setReflectionEnabled(int enabled) {
	this->reflectionEnabled = enabled;
}

int SceneManager::getReflectionEnabled() {
	return this->reflectionEnabled;
}

void SceneManager::setAmbientEnabled(int enabled) {
	this->ambientEnabled = enabled;
}

int SceneManager::getAmbientEnabled() {
	return this->ambientEnabled;
}
