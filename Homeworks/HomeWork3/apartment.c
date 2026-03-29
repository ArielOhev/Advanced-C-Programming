#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "apartment.h"

apartment* createApartmentArr(apartment* apart_units, int size, int numbers, int maxPrice,int *Number) {
	int newSize = 0;
	apartment* newArr = (apartment*)malloc(size * sizeof(apartment));
	for (int i = 0; i < size; i++) {
		if(apart_units[i].rooms == numbers && apart_units[i].price <= maxPrice) {
			newArr[newSize] = apart_units[i];
			newSize++;
		}
	}

	newArr = (apartment*)realloc(newArr, newSize * sizeof(apartment));
	assert(newArr != NULL);
	*Number = newSize;
	return newArr;

}
