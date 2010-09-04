/*
 * SphereTest.cc
 *
 *  Created on: 24-Jan-2009
 *      Author: will
 */

#include "PlaneTest.hh"

CPPUNIT_TEST_SUITE_REGISTRATION (PlaneTest);

#define TOLERANCE 0.01

void PlaneTest::setUp()
{
	this->a = new Plane(Vector3f(0.0f, 1.0f, 0.0f), 0.0f);
}

void PlaneTest::tearDown()
{
}

void PlaneTest::IntersectTest()
{
	/*
	float distance = 0.0f;
	Vector3f* origin = new Vector3f(-5,0,0);
	Vector3f* direction = new Vector3f(1,0,0);

	Primitive::Intersection i = a->intersectsRay(*origin, *direction, distance);

	CPPUNIT_ASSERT_EQUAL(Primitive::Hit, i);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(4.0f, distance, TOLERANCE);*/
}

void PlaneTest::ReflectRayTest()
{
	Vector3f point	  ( 0.0f,  0.0f, 0.0f);
	Vector3f direction(-1.0f, -1.0f, 0.0f);
	Vector3f expected (-1.0f,  1.0f, 0.0f);

	CPPUNIT_ASSERT(a->getReflectionRay(point, direction) == expected);
}
