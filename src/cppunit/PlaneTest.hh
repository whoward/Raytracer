#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

#include "../primitives/Primitive.hh"
#include "../primitives/Plane.hh"

class PlaneTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (PlaneTest);
	CPPUNIT_TEST (IntersectTest);
	CPPUNIT_TEST (ReflectRayTest);
	CPPUNIT_TEST_SUITE_END ();

	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void IntersectTest(void);
		void ReflectRayTest(void);
	private:
		Plane* a;
};
