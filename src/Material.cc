/*
 * Material.cc
 *
 *  Created on: 24-Jan-2009
 *      Author: will
 */

#include "Material.hh"

Material::Material() {
	this->diffuse = 0.8f;
	this->reflection = 0.0f;
	this->ambient = 0.0f;
	this->phong = 50.0f;
}

Material::Material(const Vector3f& color, const float& diffuse, const float& reflection, const float& ambience, const float& phong)
{
	this->colour = color;
	this->diffuse = diffuse;
	this->reflection = reflection;
	this->ambient = ambience;
	this->phong = phong;
}

void	 Material::setColour( Vector3f& color)
{
	this->colour = color;
}
Vector3f Material::getColour()
{
	return this->colour;
}

void Material::setAmbient( float& ambient)
{
	this->ambient = ambient;
}
float Material::getAmbient()
{
	return this->ambient;
}

void 	 Material::setDiffuse( float& diffuse)
{
	this->diffuse = diffuse;
}
float	 Material::getDiffuse()
{
	return this->diffuse;
}

void	 Material::setReflection( float& reflection)
{
	this->reflection = reflection;
}
float	 Material::getReflection()
{
	return this->reflection;
}

float	 Material::getSpecular()
{
	return 1.0f - this->getDiffuse();
}

void	 Material::setPhongExponent( float& phong)
{
	this->phong = phong;
}
float	 Material::getPhongExponent()
{
	return this->phong;
}
