/*
 * Matrix44f.cc
 *
 *  Created on: 4-Feb-2009
 *      Author: will
 */

#include "Matrix44f.hh"

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

Matrix44f::Matrix44f() {
	for(unsigned int i = 0; i < 4; i++)
		for(unsigned int j = 0; j < 4; j++)
			this->values[i][j] = 0.0f;
}

Matrix44f::Matrix44f(
	float e00, float e01, float e02, float e03,
	float e10, float e11, float e12, float e13,
	float e20, float e21, float e22, float e23,
	float e30, float e31, float e32, float e33)
{
	this->values[0][0] = e00;
	this->values[0][1] = e01;
	this->values[0][2] = e02;
	this->values[0][3] = e03;
	this->values[1][0] = e10;
	this->values[1][1] = e11;
	this->values[1][2] = e12;
	this->values[1][3] = e13;
	this->values[2][0] = e20;
	this->values[2][1] = e21;
	this->values[2][2] = e22;
	this->values[2][3] = e23;
	this->values[3][0] = e30;
	this->values[3][1] = e31;
	this->values[3][2] = e32;
	this->values[3][3] = e33;
}

Matrix44f Matrix44f::RotationMatrixX(float x) {
	return Matrix44f(1,       0, 	  0, 	0,
					 0,  cos(x), -sin(x), 	0,
					 0,  sin(x),  cos(x), 	0,
					 0,       0,       0, 	0);
}

Matrix44f Matrix44f::RotationMatrixY(float y) {
	return Matrix44f(cos(y),      0,   sin(y), 	   0,
						  0,      1,        0, 	   0,
				    -sin(y),      0,   cos(y), 	   0,
				 		  0,      0,        0,     0);
}

Matrix44f Matrix44f::RotationMatrixZ(float z) {
	return Matrix44f(cos(z),-sin(z),       0, 	0,
					 sin(z), cos(z),       0, 	0,
						  0,      0,       1, 	0,
						  0,      0,       0, 	0);
}

Matrix44f Matrix44f::RotationMatrix(float x, float y, float z) {
	Matrix44f result = Matrix44f::IdentityMatrix();

	if(x > 0.0f)
		result *= Matrix44f::RotationMatrixX(x);
	if(y > 0.0f)
		result *= Matrix44f::RotationMatrixY(y);
	if(z > 0.0f)
		result *= Matrix44f::RotationMatrixZ(z);

	return result;
}

Matrix44f Matrix44f::IdentityMatrix() {
	return Matrix44f(1, 0, 0, 0,
					 0, 1, 0, 0,
					 0, 0, 1, 0,
					 0, 0, 0, 1);
}

float Matrix44f::get(int row, int col) {
	return this->values[row][col];
}

void Matrix44f::set(int row, int col, float val) {
	this->values[row][col] = val;
}

Matrix44f operator*( Matrix44f& a, Matrix44f& b ) {
	Matrix44f result;

	for(unsigned int i = 0; i < 4; i++)
		for(unsigned int j = 0; j < 4; j++)
			for(unsigned int r = 0; r < 4; r++)
				result.set(i,j, result.get(i,j) + a.get(i,r) * b.get(r, j));

	return result;
}

Vector3f operator*(Matrix44f& r, Vector3f& v) {
	Vector3f result;
	result.x = v.x * r.values[0][0] + v.y * r.values[0][1] + v.z * r.values[0][2];
	result.y = v.x * r.values[1][0] + v.y * r.values[1][1] + v.z * r.values[1][2];
	result.z = v.x * r.values[2][0] + v.y * r.values[2][1] + v.z * r.values[2][2];
	return result;
}

Matrix44f Matrix44f::operator*=(Matrix44f rhs) {
	Matrix44f result = *this * rhs;
	for(unsigned int i = 0; i < 4; i++)
		for(unsigned int j = 0; j < 4; j++)
			this->values[i][j] = result.get(i,j);
}

const string Matrix44f::toString() {
	ostringstream s;
	for(unsigned int i = 0; i < 4; i++) {
		s << "[ ";
		for(unsigned int j = 0; j < 4; j++)
			s << setw(10) << setprecision(2) << fixed << this->values[i][j] << ((j != 3)?", ":"");
		s << " ]\n";
	}

	return s.str();
}
