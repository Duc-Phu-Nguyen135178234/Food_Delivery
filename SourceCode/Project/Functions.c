#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"
#include "mapping.h"
#include "data.h"

int getInput(const struct Map* routeMap, struct PackageInf* package, char* teststr) {
	int valid = 0;
	int weight = 0;
	double boxSize = 0.0;
	char dest[BUFFER];
	char buffer[BUFFER];
	if (routeMap != NULL) {
		if (teststr == NULL) {
			do {
				printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
				if (scanf("%d %lf %s", &weight, &boxSize, &dest) == 3) {
					while (getchar() != '\n');
					dest[strlen(dest)] = '\0';

					if (weight == 0 && boxSize == 0 && strcmp(dest, "x") == 0) {
						printf("Thank you for shipping with Seneca!\n");
						valid = -1;
					}

					if (valid != -1) {
						if (!Validdestination(routeMap, dest))
						{
							printf("invalid destination\n");
							valid = 0;
						}
						else {
							valid = 1;

							package->m_destination = dest;

							if (!checkBoxSize(boxSize)) {
								valid = 0;
								printf("Invalid size\n");
							}
							else {
								valid = 1;
								package->m_boxSize = boxSize;

								if (!validBoxWeight(weight)) {
									valid = 0;
									printf("Invalid weight (must be 1-1200 Kg.)\n");
								}
								else {
									valid = 1;
									package->m_weight = weight;
								}
							}
						}
					}
				}
				else {
					puts("Enter correct values");
					fflush(stdin);
					while (getchar() != '\n');
					valid = 0;
				}
			} while (valid != 1 && valid != -1);
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
	fflush(stdin);
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

int Validdestination(const struct Map* routeMap, char* dest) {
	int len = strlen(dest);
	int row;
	char col;

	if (len >= 2 && len <= 3) {
		// Check if the last character is a letter
		if (!isalpha(dest[len - 1])) return 0;


		row = atoi(dest); // Change this line to only convert the digits

		// Extract the column letter part of the destination
		col = toupper(dest[len - 1]);
		dest[len - 1] = toupper(dest[len - 1]);
		if (row < 1 || row > MAP_ROWS) return 0; // out of range

		if (!isValidColumn(col)) return 0; // if the column letter is out of range


		// Check if the square at the destination is occupied by a building
		return (routeMap->squares[row - 1][col - 'A'] == 1) ? 1 : 0; // Building present

		//return 1; // Destination is valid and accessible

	}
	return 0; // Destination format invalid
}

int checkSpaceOfTruck(double space, struct Truck* truck1) {
	if (truck1->m_totalSpace + space > BOX_SPACE) {

		//printf("Error: The total space of the truck cannot exceed %d cubic meters.\n", BOX_SPACE);
		return 0;
	}
	else {
		truck1->m_totalSpace += space;
		return 1;
	}
}


int checkBoxSize(double shipmentSize) {

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
		truck->m_totalWeight += package->m_weight;
		return 1; // Can safely add package, return true
	}
}
struct Point calcClosestPointeFromRoute(const struct Route* r1, struct Point* dest) {
	int i = 0;
	double results[100] = { -1.0 };
	double min = 0;
	int index = 0;
	for (i = 0; i < r1->numPoints; i++) {
		results[i] = distance(&r1->points[i], dest);
	}
	min = results[0];
	for (i = 0; i < r1->numPoints; i++) {
		if (results[i] < min) {
			min = results[i];
			index = i;
		}
	}
	//printf("%d\n", index + 1);
	return r1->points[index];
}

int validBoxWeight(int weight) {
	if (weight <= HIGH_WEIGHT && weight >= LOW_WEIGHT) {
		return 1;
	}
	else {
		return 0;
	}
}

void printPoint(const struct Point* point, int end) {
	int col = point->col;
	int row = point->row;
	char c = col + 'A';
	char r = row;
	if (!col && !row) {}
	else {
		if (!end) {
			printf("%d%c, ", row + 1, c);
		}
		else {
			printf("%d%c", row + 1, c);
		}
	}

}

struct Point convertPoint(const struct PackageInf* currentPackage) {
	struct Point destinationPoint;
	if (strlen(currentPackage->m_destination) == 2) {
		char copy[3] = { '\0' };
		char c[2] = { '\0' };
		strncpy(copy, currentPackage->m_destination, 2);
		strncpy(c, copy, 1);
		destinationPoint.row = atoi(c) - 1;
		destinationPoint.col = copy[1] - 'A';
	}
	else if (strlen(currentPackage->m_destination) == 3) {
		char copy[4] = { '\0' };
		char c[3] = { '\0' };
		strncpy(copy, currentPackage->m_destination, 3);
		strncpy(c, copy, 2);
		destinationPoint.row = atoi(c) - 1;
		destinationPoint.col = copy[2] - 'A';
	}

	return destinationPoint;
}

int handleInnerPoint(struct Point* point, struct Map* map, struct Point* start) {
	const int max = 10;
	struct Point testPoint;
	testPoint.col = point->col;
	testPoint.row = point->row;
	double close[4] = {0.0};
	double close2[3] = { 0.0 };
	double smallest, smallest2;
	int found = 0, k = 0, flag = 0;
	int index = 0, index2 = 0;
	int shift = 0, shift2 = 0, shift3 = 0;
	int row = point->row;
	int col = point->col;

	// Check if the point is surrounded by 1s
	if (map->squares[row - 1][col] == 1 &&
		map->squares[row][col - 1] == 1 &&
		map->squares[row][col + 1] == 1 &&
		map->squares[row + 1][col] == 1) {

		//Clockwise
		testPoint.row--;
		close[0] = distance(&testPoint, start);
		testPoint.row++;
		testPoint.col++;
		close[1] = distance(&testPoint, start);
		testPoint.col--;
		testPoint.row++;
		close[2] = distance(&testPoint, start);
		testPoint.row--;
		testPoint.col--;
		close[3] = distance(&testPoint, start);
		testPoint.col++;

		smallest = close[0];
		index = 0;
		for (int i = 1; i < 4; i++) {
			if (smallest > close[i]) {
				smallest = close[i];
				index = i;
			}
		}
		for (int j = 0;j < 4;j++) {
			if (close[j] != close[index]) {
				close2[k] = close[j];
				k++;
			}
		}
		smallest2 = close2[0];
		for (int i = 1; i < 3; i++) {
			if (smallest2 > close2[i]) {
				smallest2 = close2[i];
				index2 = i;
			}
		}
		if (index2 == 1) {
			index2 = 2;
		}
		if (fabs(close2[0] - close2[2]) < 0.000001) {
			flag = 1;
		}

		if (index == 0) {
			for (int i = 1; i < max && !found; i++) {
				if (map->squares[row - i][col] == 0) {
					found = 1;
				}
				else {
					shift--;
				}
			}
			found = 0;
			if (index2 == 0) {
				for (int i = 1; i < max && !found; i++) {
					if (map->squares[row][col + i] == 0) {
						found = 1;
					}
					else {
						shift2++;
					}
				}
				found = 0;
				if (flag) {
					for (int i = 1; i < max && !found; i++) {
						if (map->squares[row][col - i] == 0) {
							found = 1;
						}
						else {
							shift3--;
						}
					}
				}
			}
			else if (index2 == 2) {
				for (int i = 1; i < max && !found; i++) {
					if (map->squares[row][col - i] == 0) {
						found = 1;
					}
					else {
						shift2--;
					}
				}
			}
		
			if (abs(shift3) < abs(shift) && abs(shift3) < abs(shift2)) {
				point->col += shift3;
			}
			else if (abs(shift) <= abs(shift2)) {
				point->row += shift;
			}
			else {
				point->col += shift2;
			}
		
		}
		else if (index == 1) {
			for (int i = 1; i < max && !found; i++) {
				if (map->squares[row][col + i] == 0) {
					found = 1;
				}
				else {
					shift++;
				}
			}
			found = 0;
			if (index2 == 0) {
				for (int i = 1; i < max && !found; i++) {
					if (map->squares[row - i][col] == 0) {
						found = 1;
					}
					else {
						shift2--;
					}
				}
			}
			else if (index2 == 2) {
				for (int i = 1; i < max && !found; i++) {
					if (map->squares[row + i][col] == 0) {
						found = 1;
					}
					else {
						shift2++;
					}
				}
			}
			if (abs(shift) <= abs(shift2)) {
				point->col += shift;
			}
			else {
				point->row += shift2;
			}
		}
		else if (index == 2) {
			for (int i = 1; i < max && !found; i++) {
				if (map->squares[row + i][col] == 0) {
					found = 1;
				}
				else {
					shift++;
				}
			}
			found = 0;
			if (index2 == 0) {
				for (int i = 1; i < max && !found; i++) {
					if (map->squares[row][col - i] == 0) {
						found = 1;
					}
					else {
						shift2--;
					}
				}
			}
			else if (index2 == 2) {
				for (int i = 1; i < max && !found; i++) {
					if (map->squares[row][col + i] == 0) {
						found = 1;
					}
					else {
						shift2++;
					}
				}
			}
			if (abs(shift) <= abs(shift2)) {
				point->row += shift;
			}
			else {
				point->col += shift2;
			}
		}
		else if (index == 3) {
			for (int i = 1; i < max && !found; i++) {
				if (map->squares[row][col-1] == 0) {
					found = 1;
				}
				else {
					shift++;
				}
			}
			found = 0;
			if (index2 == 0) {
				for (int i = 1; i < max && !found; i++) {
					if (map->squares[row+i][col] == 0) {
						found = 1;
					}
					else {
						shift2++;
					}
				}
			}
			else if (index2 == 2) {
				for (int i = 1; i < max && !found; i++) {
					if (map->squares[row-i][col] == 0) {
						found = 1;
					}
					else {
						shift2--;
					}
				}
			}
			if (abs(shift) <= abs(shift2)) {
				point->col += shift;
			}
			else {
				point->row += shift2;
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}
void sortPoints(double *arr, int *indexes) {
	if (arr[0] > arr[2]) {
		//swap(&arr[0], &arr[2]);
		swap(&indexes[0], &indexes[2]);
	}
	if (arr[0] > arr[1]) {
		//swap(&arr[0], &arr[1]);
		swap(&indexes[0], &indexes[1]);
	}
	if (arr[1] > arr[2]) {
		//swap(&arr[1], &arr[2]);
		swap(&indexes[1], &indexes[2]);
	}
}
void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}