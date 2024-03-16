#pragma once

#include "data.h"

struct Truck {
	int num_packages;     //Package Count
	PackageInf p; // Package List
	double m_totalSpace; //cubic meters. Cannot exceed BOX_SPACE
	double m_totalWeight; // KG. Cannot exceed MAX_CARGO
	char* route;          // assigned route
};