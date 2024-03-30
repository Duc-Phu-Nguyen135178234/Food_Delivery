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
           

        TEST_METHOD(validdestination_1A)

        {
            struct Map routeMap = populateMap();
            char dest[] = "1A"; 

         
            int result = Validdestination(&routeMap, dest);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(validdestination_25Y)
        {
            struct Map routeMap = populateMap();
            char dest[] = "25Y"; // Building present

           
            int result = Validdestination(&routeMap, dest);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(validdestination_10M)
        {
            struct Map routeMap = populateMap();
            char dest[] = "10M"; // out range

         
            int result = Validdestination(&routeMap, dest);

            
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(validdestination_23U)
        {
            struct Map routeMap = populateMap();
            char dest[] = "23U"; // Building present

            int result = Validdestination(&routeMap, dest);

            
            Assert::AreEqual(1, result);
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
            int valid = getInput(&testMap, NULL,"0 0 1A");
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
