//Header file 
#define LOW_WEIGHT 1 //KG
#define HIGH_WEIGHT 1200 //kg

//PACKAGE SIZES. Cubic Meters.
#define SZ_MIN 0.25
#define SZ_MID 0.5 
#define SZ_MAX 1 

#define destination 3

struct PackageInf {
	double m_weight;  
	double m_boxSize; 
	char* m_destination;
};
