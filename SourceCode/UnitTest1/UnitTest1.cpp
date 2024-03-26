#include "pch.h"
#include "CppUnitTest.h"
#include "functions_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(distanceFunction)
    {
    public:

        TEST_METHOD(TestValidPoints)
        {

            Point p1 = { 'a', '5' };
            Point p2 = { 'b', '5' };
            double a = distance(&p1, &p2);
            Assert::AreEqual(1.0, a);
        }
    };


   TEST_CLASS(validdestination)
    {
    public:
           

        TEST_METHOD(validdestination_1A)

        {
            struct Map routeMap = populateMap();
            char dest[] = "1A"; 

         
            int result = Validdestination(&routeMap, dest);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(validdestination_8A)
        {
            struct Map routeMap = populateMap();
            char dest[] = "8A"; // Building present

           
            int result = Validdestination(&routeMap, dest);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(validdestination_20Z)
        {
            struct Map routeMap = populateMap();
            char dest[] = "20Z"; // out range

         
            int result = Validdestination(&routeMap, dest);

            
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(validdestination_12A)
        {
            struct Map routeMap = populateMap();
            char dest[] = "12A"; // Building present

            int result = Validdestination(&routeMap, dest);

            
            Assert::AreEqual(1, result);
        }
    };

    TEST_CLASS(getinput) {
    public:
        const struct Map testMap = populateMap();
        TEST_METHOD(getInput_NULLMap) {
            const struct Map* map = NULL;
            int valid = getInput(map, NULL);
            Assert::IsFalse(valid);
        }
        TEST_METHOD(getInput_empty) {
            char test[] = "\0";
            int valid = getInput(&testMap, test);
            Assert::IsFalse(valid);
        }
        TEST_METHOD(getInput_Exit) {
            int valid = getInput(&testMap, "0 0 x");
            Assert::AreEqual(-1, valid);
        }
        TEST_METHOD(getInput_validDestination) {
            int valid = getInput(&testMap, "0 0 1A");
            Assert::IsTrue(valid);
        }
    };
}





// Include your function declaration
int checkBoxSize(double shipmentSize){
public:
    
    // Define your test cases
    TEST_METHOD(shipmentSize_Null) {
        double shipmentSize = NULL;
        int result = checkBoxSize(boxSize);
        Assert::IsFalse(valid);
    }
    
    TEST_METHOD(shipmentSize_1) {
        double shipmentSize = 1 ;
        int result = checkBoxSize(boxSize);
        Assert::IsTrue(valid);
    }
    
    TEST_METHOD(shipmentSize_7) {
        double shipmentSize = 7;
        int result = checkBoxSize(boxSize);
        Assert::IsFalse(valid);
    }
    
    TEST_METHOD(shipmentSize_character) {
        char shipmentSize = abc;
        int result = checkBoxSize(boxSize);
        Assert::IsFalse(valid);
    }
    
}

