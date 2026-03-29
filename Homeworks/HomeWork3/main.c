#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "complex.h"
#include "student.h"
#include "apartment.h"

int main() {
    //Quest1
    //Complex c1, c2, sum;

    //inputComplex(&c1);
    //inputComplex(&c2);

    //sum = sumComplex(c1, c2);
    //printComplex(sum);

	//Quest2

    student a1 = { "ariel",324,90 }, a2 = { "noy",323,70 }, a3 = {"liav",322,80};
	student students[3] = { a1, a2, a3 };

    int avg;
    int count= countAvg(students, 3, &avg);
	printf("Average grade: %d\n", avg);
    printf("%d\n", count);

	//Quest3

    apartment apts[5] = {
        {"Tel-Aviv", 2, 1500.0},
        {"Ramat", 3, 2000.0},
        {"Yeh", 2, 1800.0},
	};

    int originalSize = 4;
    int requestedRooms = 3;
    int budget = 3000;
    int finalCount = 0;

	apartment* filteredApts = createApartmentArr(apts, originalSize, requestedRooms, budget, &finalCount);

    printf("Found %d apartments for you:\n", finalCount);

    for (int i = 0; i < finalCount; i++) {
        printf("Address: %s, Rooms: %d, Price: %f\n",
            filteredApts[i].address, filteredApts[i].rooms, filteredApts[i].price);
    }
	free(filteredApts);

    return 0;
}