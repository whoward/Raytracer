/*
 * Matrix44f.hh
 *
 *  Created on: 4-Feb-2009
 *      Author: will
 */

#ifndef MATRIX44F_HH_
#define MATRIX44F_HH_

#include <string>
#include "Vector3f.hh"

using namespace std;

class Matrix44f
{
public:
	Matrix44f();
	Matrix44f(float e00, float e01, float e02, float e03,
			  float e10, float e11, float e12, float e13,
			  float e20, float e21, float e22, float e23,
			  float e30, float e31, float e32, float e33);

	static Matrix44f RotationMatrix(float rad_x, float rad_y, float rad_z);
	static Matrix44f RotationMatrixX(float rad_x);
	static Matrix44f RotationMatrixY(float rad_y);
	static Matrix44f RotationMatrixZ(float rad_z);

	static Matrix44f IdentityMatrix();

	friend Matrix44f operator*(Matrix44f& a, Matrix44f& b);
	friend Vector3f operator*(Matrix44f& r, Vector3f& v);

	Matrix44f operator*=(Matrix44f rhs);

	float get(int row, int col);
	void set(int row, int col, float val);

	const string toString();

protected:
	float values[4][4];
};

#endif /* MATRIX44F_HH_ */
