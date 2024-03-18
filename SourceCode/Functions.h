
#ifndef SENECA_DELIVERY_H
#define SENECA_DELIVERY_H
//header file for 6 function

//Create function prototype getInput
void getInput(struct packageInf* p);
/*Prompt the user for input and store by address to a packageInf* object
* Include Validation for user input before storing to data structure
*/

//Create function prototype check Packageweight


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

//create function prototype Validdestination
int Validdestination(const struct Map* routeMap, char* destination);
// get char destination[] with size of 4 
// check if correct format 8A 12A and map destination on routeMap return 1
//if Destination out size the routeMap return 0


//create function prototype check space of truck
int checkSpaceOfTruck(int length, int width, int height, int availableLength, int availableWidth, int availableHeight);
//this prototype will take 6 values  and returns integer value
//
#endif //SENECA_DELIVERY_H
