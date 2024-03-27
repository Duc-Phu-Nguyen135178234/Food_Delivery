#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "data.h"
#include "Functions.h"

int main(void)
{
	struct Truck truck1 = { 0, 0.0, 0.0, BLUE };
	struct Truck truck2 = { 0, 0.0, 0.0, YELLOW };
	struct Truck truck3 = { 0, 0.0, 0.0, GREEN };
	struct Truck trucks[3] = { truck1, truck2, truck3 };
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Map routeMap = addRoute(&baseMap, &blueRoute);

	struct Point p1 = { 'a', '1' };
	struct Point p2 = { 'b', '2' };
	double a = distance(&p1, &p2);
	printf("%lf\n", a);

	printMap(&routeMap, 1, 1);
	getInput(&routeMap, NULL);
	
	return 0;
}