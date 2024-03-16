
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

//create function prototype Validdestination
int Validdestination(const struct Map* routeMap, char* destination);
// get char destination[] with size of 4 
// check if correct format 8A 12A and map destination on routeMap return 1
//if Destination out size the routeMap return 0


//create function prototype check space of truck

#endif //SENECA_DELIVERY_H