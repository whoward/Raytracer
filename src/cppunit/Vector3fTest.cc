/*
 * Vector3fTest.cc
 *
 *  Created on: 24-Jan-2009
 *      Author: will
 */
#include "Vector3fTest.hh"

CPPUNIT_TEST_SUITE_REGISTRATION (Vector3fTest);

#define TOLERANCE 0.001

void Vector3fTest::setUp(void)
{
	// Null Vector
	this->a = new Vector3f();
	this->b = new Vector3f(0,0,0);

	// Unit Vectors
	this->c = new Vector3f(1,0,0);
	this->d = new Vector3f(0,1,0);
	this->e = new Vector3f(0,0,1);

	// Regular Vector
	this->f = new Vector3f(5,3,2);

	// Negative Vector
	this->g = new Vector3f(-10,-5,-3);
}

void Vector3fTest::tearDown(void)
{
}

void Vector3fTest::TestConstructor1(void)
{
	CPPUNIT_ASSERT(a.x == 0);
	CPPUNIT_ASSERT(a.y == 0);
	CPPUNIT_ASSERT(a.z == 0);
}

void Vector3fTest::TestConstructor2(void)
{
	CPPUNIT_ASSERT(b.x == 0);
	CPPUNIT_ASSERT(b.y == 0);
	CPPUNIT_ASSERT(b.z == 0);
}

void Vector3fTest::TestOpAssignment(void)
{
	f = g;
	CPPUNIT_ASSERT(f.x == g.x);
	CPPUNIT_ASSERT(f.y == g.y);
	CPPUNIT_ASSERT(f.z == g.z);
	CPPUNIT_ASSERT(&f != &g);
}

void Vector3fTest::TestOpAdd(void)
{
	Vector3f sum = c + d;
	CPPUNIT_ASSERT(sum.x == 1);
	CPPUNIT_ASSERT(sum.y == 1);
	CPPUNIT_ASSERT(sum.z == 0);

	CPPUNIT_ASSERT(&sum != &c);
	CPPUNIT_ASSERT(&sum != &d);
}

void Vector3fTest::TestOpSub(void)
{
	Vector3f diff = f - e - e;
	CPPUNIT_ASSERT(diff.x == 5);
	CPPUNIT_ASSERT(diff.y == 3);
	CPPUNIT_ASSERT(diff.z == 0);

	CPPUNIT_ASSERT(&diff != &f);
	CPPUNIT_ASSERT(&diff != &e);
}

void Vector3fTest::TestOpNegative(void)
{
	Vector3f neg = -g;
	CPPUNIT_ASSERT(neg.x == 10);
	CPPUNIT_ASSERT(neg.y == 5);
	CPPUNIT_ASSERT(neg.z == 3);

	CPPUNIT_ASSERT(&neg != &g);
}

void Vector3fTest::TestOpMult(void)
{
	Vector3f mult = f * g;

	CPPUNIT_ASSERT(mult.x == -50);
	CPPUNIT_ASSERT(mult.y == -15);
	CPPUNIT_ASSERT(mult.z == -6);

	CPPUNIT_ASSERT(&mult != &f);
	CPPUNIT_ASSERT(&mult != &g);
}

void Vector3fTest::TestOpScaleFloat(void)
{
	Vector3f scale = f * 5.0f;

	CPPUNIT_ASSERT(scale.x == 25.0f);
	CPPUNIT_ASSERT(scale.y == 15.0f);
	CPPUNIT_ASSERT(scale.z == 10.0f);

	CPPUNIT_ASSERT(&scale != &f);
}

void Vector3fTest::TestOpScaleInt(void)
{
	Vector3f scale = f * 5;

	CPPUNIT_ASSERT(scale.x == 25.0f);
	CPPUNIT_ASSERT(scale.y == 15.0f);
	CPPUNIT_ASSERT(scale.z == 10.0f);

	CPPUNIT_ASSERT(&scale != &f);
}

void Vector3fTest::TestOpCrossProduct(void)
{
	Vector3f cproduct = f ^ g;

	CPPUNIT_ASSERT(cproduct.x ==  1.0f);
	CPPUNIT_ASSERT(cproduct.y == -5.0f);
	CPPUNIT_ASSERT(cproduct.z ==  5.0f);

	CPPUNIT_ASSERT(&cproduct != &f);
	CPPUNIT_ASSERT(&cproduct != &g);
}

void Vector3fTest::TestOpDotProduct(void)
{
	CPPUNIT_ASSERT(f.dotproduct(g) == -71.0f);
}

void Vector3fTest::TestOpEquality(void)
{
	CPPUNIT_ASSERT(a == b);
	CPPUNIT_ASSERT(&a != &b);
}

void Vector3fTest::TestOpInequality(void)
{
	CPPUNIT_ASSERT(f != g);
	CPPUNIT_ASSERT(&f != &g);
}

void Vector3fTest::TestNormalize(void)
{
	Vector3f test = f.normalize();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.81110710565381272f, test.x, TOLERANCE);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.48666426339228763f, test.y, TOLERANCE);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.32444284226152509f, test.z, TOLERANCE);

}

void Vector3fTest::TestLength(void)
{
	CPPUNIT_ASSERT_DOUBLES_EQUAL(6.164414002968976f, f.length(), TOLERANCE);
}
