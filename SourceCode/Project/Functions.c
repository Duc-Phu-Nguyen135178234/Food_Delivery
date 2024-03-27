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

				if (weight == 0 && boxSize == 0 && strcmp(dest, "x") == 0) {
					exit = 1;
				}

				if (!exit) {
					if (!Validdestination(routeMap, dest))
					{
						printf("invalid destination\n");
						valid = 0;
					}
					else {
						valid = 1;
						
						if (checkBoxSize(boxSize)) {
							valid = 1;
						}
						else {
							valid = 0;
							printf("Invalid size\n");
						}
					}
					
				}
				//checkWeight(truck, package);

				//checkSpaceOfTruck()
			
			} while (!valid && !exit);
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


int checkBoxSize(double shipmentSize) {
    
    //const double size1 = 0.5;
    //const double size2 = 1.0;
    //const double size3 = 5.0;
    int result = 0;

    if (shipmentSize == SIZE1 || shipmentSize == SIZE2 || shipmentSize == SIZE3) {
        //printf("Box size is valid.\n");
        result = 1;
        
    } else {
		result = 0;
    }

    return result;
}

int checkWeight(struct Truck* truck, struct PackageInf* package) {
	// Check if pointers are valid
	if (truck == NULL || package == NULL) {
		return 0; // Return false if either pointer is null, indicating an error
	}

	// Calculate new total weight if package is added to truck
	double newTotalWeight = truck->m_totalWeight + package->m_weight;

	// Check if the new total weight exceeds the truck's weight limit
	if (newTotalWeight > HIGH_WEIGHT) {
		return 0; // Cannot add package without exceeding limit, return false
	}
	else {
		return 1; // Can safely add package, return true
	}
}
