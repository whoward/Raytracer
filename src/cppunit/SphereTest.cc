/*
 * SphereTest.cc
 *
 *  Created on: 24-Jan-2009
 *      Author: will
 */

#include "SphereTest.hh"

CPPUNIT_TEST_SUITE_REGISTRATION (SphereTest);

#define TOLERANCE 0.01

void SphereTest::setUp()
{
	this->a = new Sphere(Vector3f(0,0,0), 1.0f);
	this->b = new Sphere(Vector3f(0,0,0), 5.0f);
}

void SphereTest::tearDown()
{
}

void SphereTest::IntersectTest()
{
	float distance = 0.0f;
	Vector3f* origin = new Vector3f(-5,0,0);
	Vector3f* direction = new Vector3f(1,0,0);

	Primitive::Intersection i = a->intersectsRay(*origin, *direction, distance);

	CPPUNIT_ASSERT_EQUAL(Primitive::Hit, i);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(4.0f, distance, TOLERANCE);
}
