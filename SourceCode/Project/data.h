//Header file 

#ifndef DATA_H
#define DATA_H
#define LOW_WEIGHT 1 //KG
#define HIGH_WEIGHT 1200 //kg
#define BOX_SPACE 50 

//PACKAGE SIZES. Cubic Meters.
#define SIZE1 0.5
#define SIZE2 1.0
#define SIZE3 5.0

#define DESTINATIONS 3 //TOGGLE ROUTES HERE

struct PackageInf {
	double m_weight;  
	double m_boxSize; 
	char* m_destination;
};

struct Truck {
	int num_packages;     //Package Count
	double m_totalSpace; //cubic meters. Cannot exceed BOX_SPACE
	double m_totalWeight; // KG. Cannot exceed MAX_CARGO
	char route;          // assigned route
};

#endif
