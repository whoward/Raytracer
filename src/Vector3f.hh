/*
 * Vector3f.hh
 *
 *  Created on: 23-Jan-2009
 *      Author: will
 */

#ifndef VECTOR3F_HH_
#define VECTOR3F_HH_

#include <string>

using namespace std;

class Vector3f
{
	public:
		Vector3f();
		Vector3f(float x, float y, float z);

		Vector3f operator=(const Vector3f& rhs);
		Vector3f operator=(const Vector3f* rhs);

		void operator+=(const Vector3f& rhs);
		void operator+=(const Vector3f* rhs);
		void operator-=(const Vector3f& rhs);
		void operator-=(const Vector3f* rhs);
		void operator*=(const Vector3f& rhs);
		void operator*=(const Vector3f* rhs);
		void operator*=(float rhs);

		Vector3f operator-();
		friend Vector3f operator+(const Vector3f& v1, const Vector3f& v2);
		friend Vector3f operator-(const Vector3f& v1, const Vector3f& v2);
		friend Vector3f operator+(const Vector3f& v1, const Vector3f* v2);
		friend Vector3f operator-(const Vector3f& v1, const Vector3f* v2);
		friend Vector3f operator*(const Vector3f& v1, const Vector3f& v2);
		friend Vector3f operator*(const Vector3f& v1, const Vector3f* v2);
		friend Vector3f operator*(const Vector3f& v1, float f);
		friend Vector3f operator*(float f, const Vector3f& v1);
		friend Vector3f operator^(const Vector3f& v1, const Vector3f& v2);
		friend Vector3f operator^(const Vector3f& v1, const Vector3f* v2);

		const bool operator==(const Vector3f& rhs);
		const bool operator!=(const Vector3f& rhs);

		Vector3f normalize();

		const float dotproduct(const Vector3f& rhs);
		const float length();

		const string toString();

		float x, y, z;
};

#endif /* VECTOR3F_HH_ */
