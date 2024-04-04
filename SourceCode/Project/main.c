#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mapping.h"
#include "data.h"
#include "Functions.h"

int main(void)
{
	int flag = 0, pass = 0, counter = 0, sendDepot = 0, notFound = 0, index = 0, i = 0;
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

	do {
		flag = getInput(&routeMap, &currentPackage, NULL);
		if (flag != -1) {
			destinationPoint = convertPoint(&currentPackage);
			for (i = 0; i < DESTINATIONS; i++) {
				closestPoints[i] = calcClosestPointeFromRoute(&routes[i], &destinationPoint);
			}
			for (i = 0; i < DESTINATIONS; i++) {
				distances[i] = distance(&closestPoints[i], &destinationPoint);
			}
			int indexes[DESTINATIONS] = { 0,1,2 };
			sortPoints(distances,indexes, DESTINATIONS);
			index = indexes[0];
			selectedRoute = routes[index];
			pass = 0, counter = 0, sendDepot = 0, notFound = 0;
			do {
				for (i = 0; i < DESTINATIONS && !pass && notFound != 3;i++) {
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
							if (divert.numPoints == -1) { //Could not find truck
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
				printPoint(&closestPoints[index],0);
				for (i = 0; i < divert.numPoints; i++) {
					if (i + 1 == divert.numPoints) {
						printPoint(&divert.points[i], 1);
					}
					else {
						printPoint(&divert.points[i], 0);
					}
				}
			}
			putchar('\n');
			//routeMap = addRoute(&routeMap, &divert);
			//printMap(&routeMap, 1, 1);
		}
	} while (flag != -1);
	return 0;
}