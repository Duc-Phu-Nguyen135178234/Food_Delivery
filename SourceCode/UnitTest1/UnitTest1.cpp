#include "pch.h"
#include "CppUnitTest.h"
#include "functions_r.h"
#include <iostream>

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
			Assert::AreEqual(1, a);
		}
	};
}
