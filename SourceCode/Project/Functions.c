#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Functions.h"

void getInput(struct packageInf* p) {
	int valid = 0;
	int weight = 0;
	double boxSize = 0.0;
	char destination[BUFFER];
	do {
		printf("Enter shipment weight, box size and destination (0 0 x to stop):");
		scanf("%d %lf %s", &weight, &boxSize, &destination);
		/*
		if (weight < 1 || weight > 1200) {
			printf("Invalid weight (must be 1-1200 Kg.)");
		}
		*/
	} while (!valid);
}