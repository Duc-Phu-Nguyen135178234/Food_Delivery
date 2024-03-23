#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
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


//function check column vaild when user input . MAP_COLS is macro define in mapping.h
int isValidColumn(char column) {
    return (column >= 'A' && column <= ('A' + MAP_COLS - 1));
}
//create function prototype Validdestination
// get char destination[]  
// check if correct format 8A 12A and map destination on routeMap return 1
//if Destination out size the routeMap return 0

int Validdestination(const struct Map* routeMap, const char* destination) {
    int len = strlen(destination);
    int row; char col;
    
    if (len<=2){
    	// Invalid destination if the first character is not a digit
	    if (!isdigit(destination[0])) return 0; 
	    
	    // Convert the row number part of the destination to an integer
	    row = atoi(destination);
	    
	     // Extract the column letter part of the destination
	    col = toupper(destination[len - 1]);
	    
	    if (row < 1 || row > MAP_COLS) return 0; // out range
	    
	    if (!isValidColumn(col, MAP_COLS)) return 0; // if the column letter is out of range
		
		// after valid destination check building or not .If building on map show 1 . not valid 
		if (routeMap->squares[row - 1][col - 'A'] == 1) return 0;
		return 1;
	}
	
	return 0;
}
