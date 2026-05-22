#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

int newPayment(char* file, char id[], double newPrice);
int main()
{
	char* fileName = "customer.txt";
	char* searchID = "330578795";
	double newPurchase = 200;

	FILE* f = fopen(fileName, "w");


	fprintf(f, "%-9s%-30s%8.2lf\n", "06842151", "Moshe", 71.25);
	fprintf(f, "%-9s%-30s%8.2lf\n", "330578795", "Benjamin", 1755.65);
	fprintf(f, "%-9s%-30s%8.2lf\n", "20051546", "Dina", 560.10);
	fclose(f);

	printf("File created. Attempting to update ID %s with amount %.1f...\n", searchID, newPurchase);

	if (newPayment(fileName, searchID, newPurchase)) {
		printf("Update successful! Check 'customer.txt' for changes.\n");
	}
	else {
		printf("Update failed. Customer ID not found or file error.\n");
	}
	
	return 0;
}

int newPayment(char *file,char id[],double newPrice){

	FILE* f = fopen(file, "r+");

	char currentID[10];
	double totalAmount;
	long pos;

	while (fscanf(f, "%9s", currentID) != EOF) {
		if (strcmp(currentID, id) == 0) {
			fseek(f, 30, SEEK_CUR);
			pos = ftell(f);

			fscanf(f, "%8lf", &totalAmount);
			totalAmount += newPrice;

			fseek(f, pos, SEEK_SET);	
			fprintf(f, "%8.2lf", totalAmount);

			fclose(f);
			return 1;
		}
		else fseek(f, 39, SEEK_CUR);
	}

	fclose(f);
	return 0;

	

}



