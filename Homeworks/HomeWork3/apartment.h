#ifndef APARTMENT_H
#define APARTMENT_H
#include <stdlib.h>

typedef struct {
	char address[30];
	int rooms;
	double price;
} apartment;

apartment* createApartmentArr(apartment *apart_units,int size,int numbers,int maxPrice,int *Number);


#endif