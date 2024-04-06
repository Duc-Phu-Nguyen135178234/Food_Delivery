#include "pch.h"
#include "CppUnitTest.h"
#include "functions_r.h"
#include "data.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(distanceFunction)
    {
    public:
        // White box tests
        TEST_METHOD(TestValidPoints)
        {

            Point p1 = { 'a', '5' };
            Point p2 = { 'b', '5' };
            double a = distance(&p1, &p2);
            Assert::AreEqual(1.0, a);
        }
        TEST_METHOD(TestTwoSpacesAlpha)
        {

            Point p1 = { 'a', '5' };
            Point p2 = { 'c', '5' };
            double a = distance(&p1, &p2);
            Assert::AreEqual(2.0, a);
        }
        TEST_METHOD(TestTwoSpacesNumbers)
        {

            Point p1 = { 'a', '5' };
            Point p2 = { 'a', '7' };
            double a = distance(&p1, &p2);
            Assert::AreEqual(2.0, a);
        }
        TEST_METHOD(Testsamepoint)
        {

            Point p1 = { 'a', '5' };
            Point p2 = { 'a', '5' };
            double a = distance(&p1, &p2);
            Assert::AreEqual(0.0, a);
        }
        TEST_METHOD(Testhypotenuse)
        {

            Point p1 = { 'a', '1' };
            Point p2 = { 'b', '2' };
            int a = distance(&p1, &p2);
            Assert::AreEqual(1, a);
        }
    };


    TEST_CLASS(validdestination)
    {
    public:


        TEST_METHOD(Blackbox_validdestination_2B)

        {
            struct Map routeMap = populateMap();
            char dest[] = "2B"; //Min of row check


            int result = Validdestination(&routeMap, dest);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(Blackbox_validdestination_8Y)
        {
            struct Map routeMap = populateMap();
            char dest[] = "8Y"; //Max of column checking


            int result = Validdestination(&routeMap, dest);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(Blackbox_validdestination_25B)
        {
            struct Map routeMap = populateMap();
            char dest[] = "25B"; //Max row checking


            int result = Validdestination(&routeMap, dest);

            
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(Blackbox_validdestination_14A)
        {
            struct Map routeMap = populateMap();
            char dest[] = "14A"; // Building present

            int result = Validdestination(&routeMap, dest);

            
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(Blackbox_validdestination_16M)
        {
            struct Map routeMap = populateMap();
            char dest[] = "16M"; // Valid inside map and present a Building have address

            int result = Validdestination(&routeMap, dest);


            Assert::AreEqual(1, result);
        }

        TEST_METHOD(Whitebox_validdestination_24F)
        {
            struct Map routeMap = populateMap();
            char dest[] = "24F"; // Valid inside map and present a Building have address

            int result = Validdestination(&routeMap, dest);


            Assert::AreEqual(1, result);
        }

        TEST_METHOD(Whitebox_validdestination_30F)
        {
            struct Map routeMap = populateMap();
            char dest[] = "30F"; //Out of map

            int result = Validdestination(&routeMap, dest);


            Assert::AreEqual(0, result);
        }

        TEST_METHOD(Whitebox_validdestination_10H)
        {
            struct Map routeMap = populateMap();
            char dest[] = "10H"; // Inside map but it is not present a Building.

            int result = Validdestination(&routeMap, dest);


            Assert::AreEqual(0, result);
        }

        TEST_METHOD(Whitebox_validdestination_17F)
        {
            struct Map routeMap = populateMap();
            char dest[] = "17F"; // Inside map but it is not present a Building.

            int result = Validdestination(&routeMap, dest);


            Assert::AreEqual(0, result);
        }
    };

    TEST_CLASS(getinput) {
    public:
        const struct Map testMap = populateMap();
        TEST_METHOD(getInput_NULLMap) {
            const struct Map* map = NULL;
            int valid = getInput(map, NULL, NULL);
            Assert::IsFalse(valid);
        }
        TEST_METHOD(getInput_empty) {
            char test[] = "\0";
            int valid = getInput(&testMap, NULL, test);
            Assert::IsFalse(valid);
        }
        TEST_METHOD(getInput_Exit) {
            int valid = getInput(&testMap, NULL,"0 0 x");
            Assert::AreEqual(-1, valid);
        }
        TEST_METHOD(getInput_validDestination) {
            int valid = getInput(&testMap, NULL,"0 0 12A");
            Assert::IsTrue(valid);
        }
    };

    TEST_CLASS(CheckWeightTests)
    {
    public:

        TEST_METHOD(MinimumValidWeight)
        {
            Truck truck = { 0, 0, 200, '\0' };
            PackageInf package = { 1, 0, nullptr };
            int result = checkWeight(&truck, &package);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(MaximumValidAddition)
        {
            Truck truck = { 0, 0, 200, '\0' };
            PackageInf package = { 1200, 0, nullptr };
            int result = checkWeight(&truck, &package);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(WeightOverMaximum)
        {
            Truck truck = { 0, 0, 0, '\0' };
            PackageInf package = { 1201, 0, nullptr };
            int result = checkWeight(&truck, &package);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TruckOverCapacity)
        {
            Truck truck = { 0, 0, 800, '\0' };
            PackageInf package = { 500, 0, nullptr };
            int result = checkWeight(&truck, &package);
            Assert::AreEqual(0, result);
        }
    };

    TEST_CLASS(checkboxsize) {

public:

    // Define your test cases
    TEST_METHOD(shipmentSize_Null) {
        double shipmentSize = NULL;
        int result = checkBoxSize(shipmentSize);
        Assert::IsFalse(result);
    }

    TEST_METHOD(shipmentSize_1) {
        double shipmentSize = 1;
        int result = checkBoxSize(shipmentSize);
        Assert::IsTrue(result);
    }

    TEST_METHOD(shipmentSize_7) {
        double shipmentSize = 7;
        int result = checkBoxSize(shipmentSize);
        Assert::IsFalse(result);
    }

    TEST_METHOD(shipmentSize_character) {
        char shipmentSize = 'a';
        int result = checkBoxSize(shipmentSize);
        Assert::IsFalse(result);
    }

    };

    TEST_CLASS(checkspaceoftruck) {

public:

    // Define your test cases
    TEST_METHOD(TestSpace15) {
        int space = 15;
        Truck tr1;
        tr1.m_totalSpace = 8;
        int result = checkSpaceOfTruck(space, &tr1);
        Assert::AreEqual(1, result);
    }

    TEST_METHOD(TestSpace6) {
        int space = 6;
        Truck tr1;
        tr1.m_totalSpace = 8;
        int result = checkSpaceOfTruck(space, &tr1);
        Assert::AreEqual(1, result);
    }

    TEST_METHOD(TestSpace10) {
        int space = 10;
        Truck tr1;
        tr1.m_totalSpace = 45;
        int result = checkSpaceOfTruck(space, &tr1);
        Assert::AreEqual(0, result);
    }

    TEST_METHOD(TestNullspace) {
        int space = 0;
        Truck tr1;
        tr1.m_totalSpace = 0;
        int result = checkSpaceOfTruck(space, &tr1);
        Assert::AreEqual(1, result);
    }

    };
}

namespace IntegrationTest {
    TEST_CLASS(IntegrationTest_getinput_check_valid) {

    public:
        TEST_METHOD(checkinput_1200_5_12A) {
            //correct weight , size , destination
            int weight = 1200;
            double size = 5.0;
            char dest[] = "12A";
            int result = 0;
            struct Map routeMap = populateMap();

            if (validBoxWeight(weight) && checkBoxSize(size)) {
                result = Validdestination(&routeMap, dest);
            }

            Assert::AreEqual(1, result);

        }
        TEST_METHOD(checkinput_1201_5_12A) {
            // invalid weight . Expect fail input 
            int weight = 1201;
            double size = 5.0;
            char dest[] = "12A";
            int result = 0;
            struct Map routeMap = populateMap();

            if (validBoxWeight(weight) && checkBoxSize(size)) {
                result = Validdestination(&routeMap, dest);
            }

            Assert::AreEqual(0, result);


        }

        TEST_METHOD(checkinput_1200_10_12A) {
            // size is invalid -->expect fail
            int weight = 1200;
            double size = 10;
            char dest[] = "12A";
            int result = 0;
            struct Map routeMap = populateMap();

            if (validBoxWeight(weight) && checkBoxSize(size)) {
                result = Validdestination(&routeMap, dest);
            }

            Assert::AreEqual(0, result);

        }

        TEST_METHOD(checkinput_1200_5_25A) {
            // destination out of box --> expect fail
            int weight = 1200;
            double size = 10;
            char dest[] = "25A";
            int result = 0;

            struct Map routeMap = populateMap();

            if (validBoxWeight(weight) && checkBoxSize(size)) {
                result = Validdestination(&routeMap, dest);
            }

            Assert::AreEqual(0, result);

        }

        TEST_METHOD(checkinput_1200_5_7J) {
            //destination inside routemap but not building --> invalid destination
            int weight = 1201;
            double size = 10;
            char dest[] = "7J";
            int result = 0;

            struct Map routeMap = populateMap();

            if (validBoxWeight(weight) && checkBoxSize(size)) {
                result = Validdestination(&routeMap, dest);
            }

            Assert::AreEqual(0, result);

        }
        TEST_METHOD(checkinput_500_0_12O) {
            //all correct input , weight , size 0.5 , 120 inside box and building . Expect function pass
            int weight = 500;
            double size = 0.5;
            char dest[] = "12O";
            int result;

            struct Map routeMap = populateMap();

            if (validBoxWeight(weight) && checkBoxSize(size)) {
                result = Validdestination(&routeMap, dest);
            }

            Assert::AreEqual(1, result);

        }

        TEST_METHOD(checkinput_1_1_22K) {
            //all correct input , weight 1, size 1 , 22K inside box and building . Expect function pass
            int weight = 1;
            double size = 0.5;
            char dest[] = "22K";
            int result;

            struct Map routeMap = populateMap();

            if (validBoxWeight(weight) && checkBoxSize(size)) {
                result = Validdestination(&routeMap, dest);
            }

            Assert::AreEqual(1, result);

        }
    };

    TEST_CLASS(IntegrationTest_boxSize_truck) {

    public:
        TEST_METHOD(checkSize1_truck) {
            struct PackageInf package = {0.0,1.0,NULL};
            struct Truck truck = {0, 0.0,0.0, '\0' };
            int result = 0;
            if (checkBoxSize(package.m_boxSize)) {
                result = checkSpaceOfTruck(package.m_boxSize, &truck);
            }
            Assert::AreEqual(1, result);
        }
        TEST_METHOD(checkSize2_truck) {
            struct PackageInf package = { 0.0,2.0,NULL };
            struct Truck truck = { 0, 0.0,0.0, '\0' };
            int result = 0;
            if (checkBoxSize(package.m_boxSize)) {
                result = checkSpaceOfTruck(package.m_boxSize, &truck);
            }
            Assert::AreEqual(0, result);
        }
        TEST_METHOD(checkSize1_truckFull) {
            struct PackageInf package = { 0.0,1.0,NULL };
            struct Truck truck = { 0, 50,0.0, '\0' };
            int result = 0;
            if (checkBoxSize(package.m_boxSize)) {
                result = checkSpaceOfTruck(package.m_boxSize, &truck);
            }
            Assert::AreEqual(0, result);
        }
        TEST_METHOD(checkSize05_truckHasSpace495) {
            struct PackageInf package = { 0.0,0.5,NULL };
            struct Truck truck = { 0, 49.5,0.0, '\0' };
            int result = 0;
            if (checkBoxSize(package.m_boxSize)) {
                result = checkSpaceOfTruck(package.m_boxSize, &truck);
            }
            Assert::AreEqual(1, result);
        }
    };
    TEST_CLASS(IntegrationTest_boxWeight_truck) {
    public:
        TEST_METHOD(checkWeightNegative_truck) {
            struct PackageInf package = { -1.0,0.5,NULL };
            struct Truck truck = { 0, 49.5,0.0, '\0' };
            int result = 0;
            if (validBoxWeight(package.m_weight)) {
                result = checkWeight(&truck, &package);
            }
            Assert::AreEqual(0, result);
        }
        TEST_METHOD(checkWeight50_truckFull) {
            struct PackageInf package = { 50.0,0.5,NULL };
            struct Truck truck = { 0,0.0,1170, '\0' };
            int result = 0;
            if (validBoxWeight(package.m_weight)) {
                result = checkWeight(&truck, &package);
            }
            Assert::AreEqual(0, result);
        }
        TEST_METHOD(checkWeight50_truckSpace) {
            struct PackageInf package = { 50.0,0.5,NULL };
            struct Truck truck = { 0, 49.5,1150, '\0' };
            int result = 0;
            if (validBoxWeight(package.m_weight)) {
                result = checkWeight(&truck, &package);
            }
            Assert::AreEqual(1, result);
        }
        TEST_METHOD(checkWeight1300_truck) {
            struct PackageInf package = { 1300.0,0.5,NULL };
            struct Truck truck = { 0, 49.5,1149, '\0' };
            int result = 0;
            if (validBoxWeight(package.m_weight)) {
                result = checkWeight(&truck, &package);
            }
            Assert::AreEqual(0, result);
        }
    };
    TEST_CLASS(IntegrationTest_ClosestPointeFromRoute_ValidDestination) {
    public:
        TEST_METHOD(ValidDestination_ClosestPointeFromRoute){
            char dest[] = "12A\0";
            struct Point destinationPoint;
            struct Point closestPoint;
            struct Route blueRoute = getBlueRoute();
            int result = 0;
            struct Map routeMap = populateMap();
            if (Validdestination(&routeMap, dest)) {
                char copy[4] = { '\0' };
                char c[3] = { '\0' };
                strncpy_s(copy, dest, 3);
                strncpy_s(c, dest, 2);
                destinationPoint.row = atoi(c) - 1;
                destinationPoint.col = copy[2] - 'A';
                closestPoint = calcClosestPointeFromRoute(&blueRoute, &destinationPoint);
                if ((int)closestPoint.row == 4 && (int)closestPoint.col == 0) {
                    result = 1;
                }
            }
            Assert::AreEqual(1, result);
        }
        TEST_METHOD(ValidDestinationFail_ClosestPointeFromRoute) {
            char dest[] = "12Z\0";
            struct Point destinationPoint;
            struct Point closestPoint;
            struct Route blueRoute = getBlueRoute();
            int result = 0;
            struct Map routeMap = populateMap();
            if (Validdestination(&routeMap, dest)) {
                char copy[4] = { '\0' };
                char c[3] = { '\0' };
                strncpy_s(copy, dest, 3);
                strncpy_s(c, dest, 2);
                destinationPoint.row = atoi(c) - 1;
                destinationPoint.col = copy[2] - 'A';
                closestPoint = calcClosestPointeFromRoute(&blueRoute, &destinationPoint);
                if ((int)closestPoint.row == 4 && (int)closestPoint.col == 0) {
                    result = 1;
                }
            }
            Assert::AreEqual(0, result);
        }
        TEST_METHOD(ValidDestinationNotBuilding_ClosestPointeFromRoute) {
            char dest[] = "11A\0";
            struct Point destinationPoint;
            struct Point closestPoint;
            struct Route blueRoute = getBlueRoute();
            int result = 0;
            struct Map routeMap = populateMap();
            if (Validdestination(&routeMap, dest)) {
                char copy[4] = { '\0' };
                char c[3] = { '\0' };
                strncpy_s(copy, dest, 3);
                strncpy_s(c, dest, 2);
                destinationPoint.row = atoi(c) - 1;
                destinationPoint.col = copy[2] - 'A';
                closestPoint = calcClosestPointeFromRoute(&blueRoute, &destinationPoint);
                if ((int)closestPoint.row == 4 && (int)closestPoint.col == 0) {
                    result = 1;
                }
            }
            Assert::AreEqual(0, result);
        }
        TEST_METHOD(ValidDestination_ClosestPointeFromRoute2) {
            char dest[] = "22G\0";
            struct Point destinationPoint;
            struct Point closestPoint;
            struct Route blueRoute = getBlueRoute();
            int result = 0;
            struct Map routeMap = populateMap();
            if (Validdestination(&routeMap, dest)) {
                char copy[4] = { '\0' };
                char c[3] = { '\0' };
                strncpy_s(copy, dest, 3);
                strncpy_s(c, dest, 2);
                destinationPoint.row = atoi(c) - 1;
                destinationPoint.col = copy[2] - 'A';
                closestPoint = calcClosestPointeFromRoute(&blueRoute, &destinationPoint);
                if ((int)closestPoint.row == 17 && (int)closestPoint.col == 10) {
                    result = 1;
                }
            }
            Assert::AreEqual(1, result);
        }
    };
}
