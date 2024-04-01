#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

	struct Point p1 = { 6, 0 };
	struct Point p2 = { 7, 0 };
	double dist = distance(&p1, &p2);

	do {
		flag = getInput(&routeMap, &currentPackage, NULL);
		if (flag != -1) {
			if (strlen(currentPackage.m_destination) == 2) {
				char copy[3] = { '\0' };
				char c[2] = { '\0' };
				strncpy(copy, currentPackage.m_destination, 2);
				strncpy(c, copy, 1);
				destinationPoint.row = atoi(c) - 1;
				destinationPoint.col = copy[1] - 'A';
			}
			else if (strlen(currentPackage.m_destination) == 3) {
				char copy[4] = { '\0' };
				char c[3] = { '\0' };
				strncpy(copy, currentPackage.m_destination, 3);
				strncpy(c, copy, 2);
				destinationPoint.row = atoi(c) - 1;
				destinationPoint.col = copy[2] - 'A';
			}
			for (int i = 0; i < 1; i++) { // ONE ROUTE ONLY FOR NOW
				closestPoint = calcClosestPointeFromRoute(&blueRoute, &destinationPoint);
				//printPoint(&closestPoint);
				int col = closestPoint.col;
				int row = closestPoint.row;
				char c = col + 'A';
				char r = row;
				printf("Starting point: %d%c\n", row + 1, c);
				struct Route route = shortestPath(&routeMap, closestPoint, destinationPoint);
				printf("On BLUE route DIVERT: ", row + 1, c);

				for (int i = 0; i < route.numPoints; i++) {
					int col = route.points[i].col;
					int row = route.points[i].row;
					char c = col + 'A';
					char r = row;
					if (!col && !row) {}
					else {
						printf("%d%c, ", row + 1, c);
					}
				}
			}
			putchar('\n');
		}
	} while (flag != -1);
	return 0;
}