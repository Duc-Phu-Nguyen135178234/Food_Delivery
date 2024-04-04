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
	double distances[DESTINATIONS];
	struct Point closestPoints[DESTINATIONS];
	struct Truck truck1 = { 0, 0.0, 0.0, BLUE };
	struct Truck truck2 = { 0, 0.0, 0.0, GREEN };
	struct Truck truck3 = { 0, 0.0, 0.0, YELLOW };
	struct Truck trucks[DESTINATIONS] = { truck1, truck2, truck3 };
	struct Truck currentTruck;
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();
	struct Route routes[DESTINATIONS] = { blueRoute, greenRoute,yellowRoute};
	struct Route selectedRoute;
	struct Route divert;
	struct Map routeMap = addRoute(&baseMap, &blueRoute);
	routeMap = addRoute(&routeMap, &greenRoute);
	routeMap = addRoute(&routeMap, &yellowRoute);

	printMap(&routeMap, 1, 1);

	struct Point p1 = { 6, 0 };
	struct Point p2 = { 7, 0 };
	double dist = distance(&p1, &p2);

	do {
		//convert point string to point struct
		flag = getInput(&routeMap, &currentPackage, NULL);
		if (flag != -1) {
			destinationPoint = convertPoint(&currentPackage);
			for (int i = 0; i < DESTINATIONS; i++) {
				closestPoints[i] = calcClosestPointeFromRoute(&routes[i], &destinationPoint);
			}
			for (int i = 0; i < DESTINATIONS; i++) {
				distances[i] = distance(&closestPoints[i], &destinationPoint);
			}
			int indexes[DESTINATIONS] = { 0,1,2 };
			sortPoints(distances,indexes, DESTINATIONS);
			int index = indexes[0];
			selectedRoute = routes[index];
			int pass = 0;
			int counter = 0;
			int sendDepot = 0;
			int notFound = 0;
			do {
				for (int i = 0; i < DESTINATIONS && !pass && notFound != 3;i++) {
					if (trucks[i].route == selectedRoute.routeSymbol) {
						if (!checkWeight(&trucks[i], &currentPackage) || !checkSpaceOfTruck(currentPackage.m_boxSize, &trucks[i])) {
							counter++;
							if (counter == DESTINATIONS) {
								sendDepot = 1;
								index = -1;
								pass = 1;
							}
							else {
								selectedRoute = routes[indexes[counter]];
								index = indexes[counter];
							}
						}
						else {
							handleInnerPoint(&destinationPoint, &routeMap, &closestPoints[index]);
							divert = shortestPath(&routeMap, closestPoints[index], destinationPoint);
							if (divert.numPoints == -1) {
								//Could not find truck
								printf("Truck could not find route\n");
								pass = 0;
								notFound++;
								if (notFound == 3) {
									pass = 1;
									index = 3;
								}
							}
							else {
								pass = 1;
							}
						}
					}
				}
			} while (!pass);
			
			if (index == 0) {
				printf("Ship on BLUE LINE,");
			}
			else if (index == 1) {
				printf("Ship on GREEN LINE,");
			}
			else if (index == 2) {
				printf("Ship on YELLOW LINE,");
			}
			else if (index == 3) {
				printf("Not an eligible point for delivery");
			}
			else {
				printf("Ships tomorrow");
				divert.numPoints = -1;
			}
			if (divert.numPoints == 0) {
				printf(" no diversion");
			}
			else if (divert.numPoints == -1){}
			else {
				printf(" divert: ");
				int col1 = closestPoints[index].col;
				int row1 = closestPoints[index].row;
				char c1 = col1 + 'A';
				printf("%d%c, ", row1 + 1, c1);
				for (int i = 0; i < divert.numPoints; i++) {
					int col = divert.points[i].col;
					int row = divert.points[i].row;
					char c = col + 'A';
					char r = row;
					if (!col && !row) {}
					else {
						printf("%d%c, ", row + 1, c);
					}
				}
			}
			putchar('\n');
			//routeMap = addRoute(&routeMap, &route);
			//printMap(&routeMap, 1, 1);
		}
	} while (flag != -1);
	return 0;
}