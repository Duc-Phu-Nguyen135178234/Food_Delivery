
#ifndef SENECA_DELIVERY_H
#define SENECA_DELIVERY_H

#include "mapping.h"
#define BUFFER 10
//header file for 6 function

//Create function prototype getInput
int getInput(const struct Map* routeMap, struct PackageInf* package, char* teststr);
/*Prompt the user for input and store by address to a packageInf* object
* Include Validation for user input before storing to data structure
*/

//Create function prototype check Packageweight
int checkWeight(struct Truck* truck, struct PackageInf* package);
//check if the weight of a package is within the permissible range for a truck
// it is considering the maximum cargo limit defined


//Create function prototype Boxsize

// Name
int checkBoxSize(double shipmentSize);
/*description: The purpose of this function is to perform a thorough check and confirm whether the box size that is given meets 
the necessary criteria for being considered as valid or not.*/

//parameters: shipmentSize
/*The function takes a parameter called ' shipmentSize ', which denotes the size of the box to be checked. To determine whether
the given size is valid or not, the function defines three constant values - 'size1', 'size2', and 'size3' - that represent the 
acceptable box sizes. The function then compares the ' shipmentSize ' parameter with these constants.*/

// returns
/*If the 'shipmentSize' matches any of the valid sizes, the function prints "valid" and returns 1 (true) to indicate that the box
size is valid or “ invalid” and returns 0(false), if it does not match.*/

int isValidColumn(char column);
//function check column vaild when user input . MAP_ROW is macro define in mapping.h.
// using inside function Validdestination

int Validdestination(const struct Map* routeMap, char* dest);
//create function prototype Validdestination
// get char destination[]  
// check if correct format 8A 12A and map destination on routeMap return 1
//if Destination out size the routeMap return 0

//create function prototype check space of truck
int checkSpaceOfTruck(double space , struct Truck* truck1);
//this prototype will take 6 values  and returns integer value
//
struct Point calcClosestPointeFromRoute(const struct Route* r1, struct Point* dest);

int validBoxWeight(int weight);

void printPoint(const struct Point* point, int end);

struct Point convertPoint(const struct PackageInf* currentPackage);

int handleInnerPoint(struct Point* point, struct Map* map, struct Point* start);

void sortPoints(double* arr, int* indexes);

void swap(int* xp, int* yp);

#endif //SENECA_DELIVERY_H