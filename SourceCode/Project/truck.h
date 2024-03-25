#pragma once

#ifndef TRUCK_H
#define TRUCK_H
//TRUCK
#define MAX_CARGO 1200 //kg
#define BOX_SPACE 50 //cubic meters

#include "data.h"

struct Truck {
	int num_packages;     //Package Count
	PackageInf p; // Package List
	double m_totalSpace; //cubic meters. Cannot exceed BOX_SPACE
	double m_totalWeight; // KG. Cannot exceed MAX_CARGO
	char* route;          // assigned route
};

#endif