/*
	Assigned by:
	Ariel Ohev 325045193
*/

#define _CRT_SECURE_NO_WARNINGS

/* Libraries */

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

/* Constant definitions */

#define N 3

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();

/* * Splits the source string into a dynamic array of words that start with a specific letter.
 * Parameters:
 * letter: The character used to filter words.
 * str: The source string containing words separated by one or more spaces.
 * p_size: A pointer to an integer that will store the total number of filtered words found.
 * Return: A pointer to a dynamically allocated array of strings.
 */
char** split(char letter, char* str, int* p_size);

/* * Creates a text file and writes a sequence of characters entered by the user.
 * Parameters:
 * filename: The name of the file to be created or overwritten.
 * Return: None.
 */
void createFile(char* filename);

/* * Analyzes a text file to determine which English letter appears most.
 * Parameters:
 * filename: The name of the file to be scanned.
 * Return: The most frequent letter.
 */
char commonestLetter(char* filename);

/* * Decodes an encrypted string in-place by shifting the ASCII value of each character.
 * Parameters:
 * text: The encrypted string to be modified.
 * Return: None.
 */
void decode(char* text);

/* Declarations of auxiliary functions */

void printStringsArray(char** str_arr, int size);
void freeMatrix(void** A, int rows);

/* ------------------------------- */

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= N; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-%d : ", N);
				scanf("%d", &select);
			} while ((select < 0) || (select > N));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			}
		} while (all_Ex_in_loop && select);
	return 0;
}


/* Function definitions */

void Ex1()
{
	char str[100];
	char letter;
	int size = 0;
	char** res_arr;

	printf("Enter a string: ");
	scanf(" %[^\n]", str);
	printf("Enter a letter: ");
	scanf(" %c", &letter);

	res_arr = split(letter, str, &size);

	if (res_arr == NULL) {
		printf("No words found starting with %c\n", letter);
	}
	else {
		printStringsArray(res_arr, size);
		freeMatrix((void**)res_arr, size);
	}
}

void Ex2()
{
	char filename[] = "input.txt";
	createFile(filename);

	char ch = commonestLetter(filename);

	if (ch != '\0') {
		printf("The commonest letter is: %c\n", ch);
	}
	else {
		printf("No letters were found in the file.\n");
	}
}

void Ex3()
{
	char text[] = "Btwlzx Dqqes Eq|pj2 Tjhvqujs Iqoqjy bpg Eqfxtx Xcwwtt";

	printf("Encrypted text:\n%s\n", text);
	decode(text);
	printf("\nDecoded text:\n%s\n", text);
}

char** split(char letter, char* str, int* p_size)
{
	int count = 0, len = 0;
	char* p = str;
	char other_letter = (letter >= 'a' && letter <= 'z') ? (letter - 'a' + 'A') :
		(letter >= 'A' && letter <= 'Z') ? (letter - 'A' + 'a') : letter;

	while (*p != '\0') {
		if (*p == letter || *p == other_letter) count++;
		while (*p != ' ' && *p != '\0') p++;
		while (*p == ' ' && *p != '\0') p++;		
	}
	
	if (count == 0) return NULL;

	*p_size = count;
	char** res = (char**)malloc(count * sizeof(char*));
	assert(res);

	p = str;
	int current_id = 0;

	while (*p) {
		while (*p == ' ') p++;
		if (*p == '\0') break;

		char* word_start = p;
		while (*p != ' ' && *p != '\0') p++;
		int word_len = p - word_start;

		if (*word_start == letter || *word_start == other_letter) {
			res[current_id] = (char*)malloc((word_len + 1) * sizeof(char));
			for (int i = 0; i < word_len; i++) {
				res[current_id][i] = word_start[i];
			}
			res[current_id][word_len] = '\0';
			current_id++;
		}
	}
	return res;


}

void createFile(char* filename)
{
	FILE* file = fopen(filename, "w");
	if (file == NULL) return;

	printf("Enter text\n");

	int c; 
	while ((c = getchar()) != EOF) {
		fputc(c, file);
	}

	fclose(file);
	printf("\nFile %s created successfully.\n", filename);
}

char commonestLetter(char* filename)
{
	FILE * fp = fopen(filename, "r");
	if (fp == NULL) return '\0';

	int counts[26] = { 0 };
	int ch;
	int letterFound = 0;

	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch >= 'a' && ch <= 'z') ch = ch - ('a' - 'A');

		if (ch >= 'A' && ch <= 'Z')
		{
			counts[ch - 'A']++;
			letterFound = 1;
		}
	}
	fclose(fp);

	if (!letterFound) return '\0';

	int maxIdx = 0;
	for (int i = 1; i < 26; i++)
	{
		if (counts[i] >= counts[maxIdx]) maxIdx = i;
	}
	return (char)(maxIdx + 'a');
}

void decode(char* text)
{
	if (text == NULL) return;

	int i = 0;
	int k = 1;

	while (text[i] != '\0')
	{
		if (text[i] == ' ') k = 1;
		else
		{
			text[i] = text[i] - k;
			k++;
		}
		i++;
	}
}



/* Definitions of auxiliary functions */

void printStringsArray(char** str_arr, int size) {
	if (size == 0) return;

	for (int i = 0; i < size; i++) {
		printf("Word %d: %s\n", i + 1, str_arr[i]);
	}
	
}
void freeMatrix(void** A, int rows) {
	if (A == NULL) return;
	for (int i = 0;i < rows;i++) {
		free(A[i]);
	}
	free(A);
}

