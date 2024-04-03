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
	//struct Point closestPoint;
	double distances[DESTINATIONS];
	struct Point closestPoints[DESTINATIONS];
	struct Truck truck1 = { 0, 0.0, 0.0, BLUE };
	struct Truck truck2 = { 0, 0.0, 0.0, GREEN };
	struct Truck truck3 = { 0, 0.0, 0.0, YELLOW };
	struct Truck trucks[3] = { truck1, truck2, truck3 };
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();
	struct Route routes[DESTINATIONS] = { blueRoute, greenRoute,yellowRoute};
	struct Route selectedRoute;
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
			for (int i = 0; i < DESTINATIONS; i++) { // ONE ROUTE ONLY FOR NOW
				closestPoints[i] = calcClosestPointeFromRoute(&routes[i], &destinationPoint);
			}
			for (int i = 0; i < DESTINATIONS; i++) {
				distances[i] = distance(&closestPoints[i], &destinationPoint);
			}
			int index = 0;
			double smallest = distances[0];
			for (int i = 0; i < DESTINATIONS; i++) {
				if (smallest > distances[i]) {
					smallest = distances[i];
					index = i;
				}
			}
			selectedRoute = routes[index];
			
			int check = handleInnerPoint(&destinationPoint, &routeMap, &closestPoints[index]);
			int col = closestPoints[index].col;
			int row = closestPoints[index].row;
			char c = col + 'A';
			int col2 = destinationPoint.col;
			int row2 = destinationPoint.row;
			char c2 = col2 + 'A';
			printf("Starting point: %d%c. Destination: %d%c\n", row + 1, c, row2+1, c2);
			struct Route route = shortestPath(&routeMap, closestPoints[index], destinationPoint);
			if (index == 0) {
				printf("Ship on BLUE LINE, divert: ", row + 1, c);
			}
			else if (index == 1) {
				printf("Ship on GREEN LINE, divert: ", row + 1, c);
			}
			else if (index == 2) {
				printf("Ship on YELLOW LINE, divert: ", row + 1, c);
			}
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
			putchar('\n');
		}
	} while (flag != -1);
	return 0;
}