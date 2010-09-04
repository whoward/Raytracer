
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "../primitives/Primitive.hh"
#include "../primitives/Sphere.hh"

class SphereTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (SphereTest);
	CPPUNIT_TEST (IntersectTest);
	CPPUNIT_TEST_SUITE_END ();

	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void IntersectTest(void);
	private:
		Sphere* a;
		Sphere* b;
};
