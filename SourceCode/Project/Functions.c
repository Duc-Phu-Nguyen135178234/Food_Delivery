#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Functions.h"
#include "data.h"

void getInput(const struct Map* routeMap) {
	int valid = 0;
	int weight = 0;
	double boxSize = 0.0;
	char dest[BUFFER];
	do {
		printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
		scanf("%d %lf %s", &weight, &boxSize, &dest);
		
		//We call check functions here? checkWeight() needs int weight parameter
		//If all checks pass then we exit loop and proceed with the calculations
		//We might want to consider some other functions since we are just checking input so far.

		//Validdestination(routeMap, dest);
		
		//checkWeight(truck, package);

		//checkBoxSize(boxSize);

		//checkSpaceOfTruck()         Send truck pointer, too many parameters.
		
		/*
		if (weight < 1 || weight > 1200) {
			printf("Invalid weight (must be 1-1200 Kg.)");
		}
		*/
	} while (!valid);
}