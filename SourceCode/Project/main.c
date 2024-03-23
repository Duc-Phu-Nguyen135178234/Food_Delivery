#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "data.h"
#include "Functions.h"

int main(void)
{
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Map routeMap = addRoute(&baseMap, &blueRoute);

	printMap(&routeMap, 1, 1);
	getInput(&routeMap, NULL);

	return 0;
}