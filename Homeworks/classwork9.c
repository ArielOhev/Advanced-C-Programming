#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

void printArr(int count[]);
int countLines(char* filename);
void letterFrequency(char* filename, int count[]);
void removeSpaces(char* infile, char* outfile);

int main()
{
	FILE* f = fopen("input.txt", "r");
	FILE* o = fopen("outfout.txt", "w");

	int count[25] = {0};

	letterFrequency(f, count);
	printArr(count);

	rewind(f);

	removeSpaces(f, o);

	fclose(o);
	fclose(f);
	
	return 0;
}

void printArr(int count[]) {
	for (int i = 0;i < 25;i++) {
		printf("%d ", count[i]);
	}
}

int countLines(char* filename) {
	int count = 1;
	char ch;

	while ((ch=fgetc(filename)) != EOF) {
		if (ch == '\n') {
			count++;
		}
	}
	return count;
}

void letterFrequency(char* filename, int count[]) {
	
	char ch;

	while((ch = fgetc(filename)) != EOF) {
		if (ch >= 'a' && ch <= 'z') {
			count[ch - 'a']++;
		}
		else if (ch >= 'A' && ch <= 'Z') {
			count[ch - 'A']++;
		}
	}
}

void removeSpaces(char *infile, char *outfile){
	char ch;

	while ((ch = fgetc(infile)) != EOF) {
		if (ch != ' ') fputc(ch, outfile);
	}
}




