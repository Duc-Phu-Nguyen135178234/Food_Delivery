
#define LOW_WEIGHT 1 //KG
#define HIGH_WEIGHT 1000 //kg

//PACKAGE SIZES. Cubic Meters.
#define SZ_MIN 0.25
#define SZ_MID 0.5 
#define SZ_MAX 1 

#define destination 

struct PackageInf {
	double m_weight;  // valid 1-1000kg
	double m_boxSize; // valid range in cubic meter: 0.25, 0.5, 1.
	char* destination;
};