#include "pch.h"
#include "CppUnitTest.h"
#include "functions_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			
			Point p1 = { 'a', '5' };
			Point p2 = { 'b', '5' };
			double a = distance(&p1, &p2);
			Assert::AreEqual(1.0, a);
		}
	};
}

TEST_CLASS(validdestination)
{
public:
    struct Map routeMap;

    // Initialize the map before running any test
    TEST_METHOD_INITIALIZE(setup) {
        routeMap = populateMap();
    }

    TEST_METHOD(validdestination_1A)
    {
        char dest[] = "1A";
        Assert::IsTrue(Validdestination(&routeMap, dest));
    }

    TEST_METHOD(validdestination_20Z)
    {
        char dest[] = "20Z";
        Assert::IsFalse(Validdestination(&routeMap, dest));
    }

    TEST_METHOD(validdestination_2B)
    {
        char dest[] = "2B";
        Assert::IsTrue(Validdestination(&routeMap, dest));
    }

    TEST_METHOD(validdestination_23Y)
    {
        char dest[] = "23Y";
        Assert::IsFalse(Validdestination(&routeMap, dest));
    }
};

