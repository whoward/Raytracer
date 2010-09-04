
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"
#include "../Vector3f.hh"

class Vector3fTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (Vector3fTest);
	CPPUNIT_TEST (TestConstructor1);
	CPPUNIT_TEST (TestConstructor2);
	CPPUNIT_TEST (TestOpAssignment);
	CPPUNIT_TEST (TestOpSub);
	CPPUNIT_TEST (TestOpNegative);
	CPPUNIT_TEST (TestOpMult);
	CPPUNIT_TEST (TestOpScaleFloat);
	CPPUNIT_TEST (TestOpScaleInt);
	CPPUNIT_TEST (TestOpCrossProduct);
	CPPUNIT_TEST (TestOpDotProduct);
	CPPUNIT_TEST (TestOpEquality);
	CPPUNIT_TEST (TestOpInequality);
	CPPUNIT_TEST (TestNormalize);
	CPPUNIT_TEST (TestLength);
	CPPUNIT_TEST_SUITE_END ();

	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void TestConstructor1(void);
		void TestConstructor2(void);

		void TestOpAssignment(void);
		void TestOpAdd(void);
		void TestOpSub(void);
		void TestOpNegative(void);
		void TestOpMult(void);
		void TestOpScaleFloat(void);
		void TestOpScaleInt(void);
		void TestOpCrossProduct(void);
		void TestOpDotProduct(void);
		void TestOpEquality(void);
		void TestOpInequality(void);

		void TestNormalize(void);
		void TestLength(void);
	private:
		Vector3f a, b, c, d, e, f, g;
};
