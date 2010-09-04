/*
 * Primitive.cc
 *
 *  Created on: 24-Jan-2009
 *      Author: will
 */

#include "Primitive.hh"
#include <iostream>

Primitive::Primitive( Vector3f pos )
{
	this->position = pos;
}

void Primitive::setPosition( Vector3f& pos)
{
	this->position = pos;
}
Vector3f Primitive::getPosition()
{
	return this->position;
}

void Primitive::setMaterial(const Material& mat)
{
	this->material = mat;
}
Material Primitive::getMaterial()
{
	return this->material;
}

void Primitive::setLight(bool value)
{
	this->light = value;
}
bool Primitive::isLight()
{
	return this->light;
}

Vector3f Primitive::getReflectionRay(Vector3f& point, Vector3f& viewdir)
{
	Vector3f normal = this->getNormal(point);

	return viewdir - ((2.0f * viewdir.dotproduct(normal)) * normal);
}
