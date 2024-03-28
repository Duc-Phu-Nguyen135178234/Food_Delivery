#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "mapping.h"
#include "data.h"
#include "Functions.h"

int main(void)
{
	int flag = 0;
	struct PackageInf currentPackage;
	struct Point destinationPoint;
	struct Point closestPoint;
	struct Truck truck1 = { 0, 0.0, 0.0, BLUE };
	struct Truck truck2 = { 0, 0.0, 0.0, YELLOW };
	struct Truck truck3 = { 0, 0.0, 0.0, GREEN };
	struct Truck trucks[3] = { truck1, truck2, truck3 };
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Map routeMap = addRoute(&baseMap, &blueRoute);

	printMap(&routeMap, 1, 1);
	//getInput(&routeMap, NULL);
	struct Point p1 = { 12,4 };
	struct Point p2 = calcClosestPointeFromRoute(&blueRoute, &p1);
	
	do {
		flag = getInput(&routeMap, &currentPackage, NULL);
		if (flag) {
			//Ship on truck code here
			if (strlen(currentPackage.m_destination) == 2) {
				destinationPoint.row = currentPackage.m_destination[0];
				destinationPoint.col = currentPackage.m_destination[1] - 'A';
			}
			else if (strlen(currentPackage.m_destination) == 3) {

			}
			for (int i = 0; i < destination; i++) {
				closestPoint = calcClosestPointeFromRoute(&blueRoute, &destinationPoint);
				int col = closestPoint.col;
				int row = closestPoint.row;
				char c = col + 'A';
				char r = row;

				printf("%d, %c\n", row + 1, c);
			}
		}
	} while (!flag);
	return 0;
}