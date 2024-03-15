//Header file 
#define LOW_WEIGHT 1 //KG
#define HIGH_WEIGHT 1000 //kg

//PACKAGE SIZES. Cubic Meters.
#define SZ_MIN 0.25
#define SZ_MID 0.5 
#define SZ_MAX 1 

//TRUCK
#define MAX_CARGO 1200 //kg
#define BOX_SPACE 50 //cubic meters


#define destination 3

struct PackageInf {
	double m_weight;  // valid 1-1000kg
	double m_boxSize; // valid range in cubic meter: 0.25, 0.5, 1.
	char* destination;
};

struct Truck {
	int num_packages;     //Package Count
	PackageInf* packages; // Package List
	double m_totalSpace; //cubic meters. Cannot exceed BOX_SPACE
	double m_totalWeight; // KG. Cannot exceed MAX_CARGO
	char* route;          // assigned route
};
