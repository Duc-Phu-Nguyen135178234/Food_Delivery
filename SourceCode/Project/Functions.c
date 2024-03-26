#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"
#include "data.h"

int getInput(const struct Map* routeMap, char* teststr) {
	int valid = 0;
	int exit = 0;
	int weight = 0;
	double boxSize = 0.0;
	char dest[BUFFER];
	if (routeMap != NULL) {
		if (teststr == NULL) {
			
			do {
				printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
				scanf("%d %lf %s", &weight, &boxSize, &dest);
				dest[strlen(dest)] = '\0';
				//We call check functions here? checkWeight() needs int weight parameter
				//If all checks pass then we exit loop and proceed with the calculations
				//We might want to consider some other functions since we are just checking input so far.

				if (weight == 0 && boxSize == 0 && strcmp(dest, "x") == 0) {
					exit = 1;
				}


				if (!Validdestination(routeMap, dest) && !exit)
				{
					printf("invalid destination\n");
					valid = 0;
				}
				else {
					valid = 1;
				}

				
				//checkWeight(truck, package);

				//checkBoxSize(boxSize);

				//checkSpaceOfTruck()         Send truck pointer, too many parameters.
				
				/*
				if (weight < 1 || weight > 1200) {
					printf("Invalid weight (must be 1-1200 Kg.)");
				}
				*/
			} while (!valid || !exit);
		}
		else {
			if (teststr[0] != '\0') {
				if (strcmp(teststr, "0 0 x") == 0) {
					valid = -1;
				}
				else {
					int weight = 0;
					double boxSize = 0.0;
					char dest[BUFFER];
					char* p;
					char test[BUFFER] = "\0";
					strcpy(test, teststr);
					p = strtok(test, " ");
					weight = atoi(p);
					p = strtok(NULL, " ");
					boxSize = atoi(p);
					p = strtok(NULL, " ");
					//p = strtok(test, " ");
					strcpy(dest, p);
					valid = Validdestination(routeMap, dest);
				}
			}
			else {
				valid = 0;
			}
		}
	}
	printf("Thank you for shipping with Seneca!\n");
	return valid;
}


//function check column vaild when user input . MAP_COLS is macro define in mapping.h
int isValidColumn(char column) {
    return (column >= 'A' && column <= ('A' + MAP_COLS - 1));
}
//create function prototype Validdestination
// get char destination[]  
// check if correct format 8A 12A and map destination on routeMap return 1
//if Destination out size the routeMap return 0

int Validdestination(const struct Map * routeMap, const char* dest) {
	int len = strlen(dest);
	int row;
	char col;

	if (len >= 2 && len <= 3) { 
		// Check if the last character is a letter
		if (!isalpha(dest[len - 1])) return 0;

	
		row = atoi(dest); // Change this line to only convert the digits

		// Extract the column letter part of the destination
		col = toupper(dest[len - 1]);

		if (row < 1 || row > MAP_ROWS) return 0; // out of range

		if (!isValidColumn(col)) return 0; // if the column letter is out of range

		
		// Check if the square at the destination is occupied by a building
		if (routeMap->squares[row - 1][col - 'A'] == 1) return 0;; // Building present

		return 1; // Destination is valid and accessible

	}


	return 0; // Destination format invalid

}

int checkSpaceOfTruck(int space, struct Truck* truck1) {
	if (truck1->m_totalSpace + space > BOX_SPACE) {

		printf("Error: The total space of the truck cannot exceed %d cubic meters.\n", BOX_SPACE);
		return 0;
	}
	else {
		truck1->m_totalSpace += space;
		return 1;
	}
}


int validCargo(float boxsize)
{
    const double minSize = 0.25;
    const double halfSize = 0.5;
    const double maxSize = 1.0;
    int result = 0;

    if (boxsize == minSize || boxsize == halfSize || boxsize == maxSize)
    {
        // printf("Box size is valid.\n"); // Corrected the printf statement
        result = 1;
    }
    else
    {
        printf("Box size is not valid.\n");
    }

    return result;
}
