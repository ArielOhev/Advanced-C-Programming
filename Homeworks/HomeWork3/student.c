#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "student.h"


void printStudent(student s) {
	printf("Name: %s\n", s.name);
	printf("ID Card: %d\n", s.id_card);
}
int countAvg(student* A, int size, int* avg) {
	int avgGrade = 0;
	int count = 0;
	for (int i = 0; i < size; i++) {
		avgGrade += A[i].grade;
	}

	avgGrade /= size;

	for (int i = 0;i < size;i++) {
		if (A[i].grade >= avgGrade) {
			count++;
			printStudent(A[i]);
		}
	}

	*avg= avgGrade;
	return count;

}
