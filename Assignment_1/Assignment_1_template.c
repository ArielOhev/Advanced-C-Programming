/*
	Assigned by:
	Ariel Ohev 325045193
*/

#define _CRT_SECURE_NO_WARNINGS

/* Libraries */

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>

/* Constant definitions */

#define N 3
#define ROWS 4
#define COLS 5

/* Type definitions */

typedef struct number
{
	unsigned long long num;
	int sum;
} Number;

typedef struct triad
{
	int i, j, value;
} Triad;

typedef struct item
{
	Triad data;
	struct item* next;
} Item;

/* Function declarations */

void Ex1();
void Ex2();
void Ex3();

Number* squareSums(unsigned long long n1, unsigned long long n2, int* p_size);
int** matrixSumNeighbor(int A[][COLS], int rows, int cols);
int createSortedSparseList(int** A, int rows, int cols, Item** lst);

/* Declarations of auxiliary functions */

int isPerfectSquare(int num);
int digitSum(unsigned long long num);

int neighborSum(int A[][COLS], int rows, int cols, int i, int j);
int** allocMatrix(int rows, int cols);

Triad createThree(int i, int j, int value);
void insert(Item** min, Item** max, Triad data);
// insert - to declare the function yourself

void printArray(Number* arr, int size);
void inputMatrix(int A[][COLS], int rows, int cols);
void printMatrix(int A[][COLS], int rows, int cols);
void printDynamicMatrix(int** A, int rows, int cols);
void freeMatrix(int** A, int rows);
void inputDynamicMatrix(int** A, int rows, int cols);
void printList(Item* lst);
void freeList(Item* lst);

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
	unsigned long long n1;
	unsigned long long n2;
	int size;

	printf("Pick your lowest number:\n");
	scanf("%llu", &n1);

	printf("Pick your largest number:\n");
	scanf("%llu", &n2);

	Number* result;

	result = squareSums(n1, n2, &size);
	printArray(result, size);

	free(result);
}

void Ex2()
{
	int A[ROWS][COLS];
	inputMatrix(A, ROWS, COLS);
	printMatrix(A, ROWS, COLS);

	printf("\n\n");

	int** B = matrixSumNeighbor(A, ROWS, COLS);
	printDynamicMatrix(B, ROWS, COLS);
	freeMatrix(B, ROWS);

}

void Ex3()
{
	int rows, cols, count;
	Item* lst = NULL; 

	printf("Enter number of rows and columns: ");
	scanf("%d %d", &rows, &cols);

	int** A = allocMatrix(rows, cols);
	inputDynamicMatrix(A, rows, cols);
	printDynamicMatrix(A, rows, cols);

	count = createSortedSparseList(A, rows, cols, &lst);

	printf("Count: %d\n", count);
	printList(lst);

	freeMatrix(A, rows);
	freeList(lst);
	

}

Number* squareSums(unsigned long long n1, unsigned long long n2, int* p_size)
{
	int capacity = 1;
	int count = 0;

	Number* result = (Number*)malloc(capacity * sizeof(Number));
	assert(result);


	for (unsigned long long i = n1; i <= n2; i++) {
		if (isPerfectSquare(digitSum(i))) {
			if (count >= capacity) {
				capacity *= 2;
				Number* temp = (Number*)realloc(result, capacity * sizeof(Number));
				assert(temp);
				result = temp;
			}
			result[count].num = i;
			result[count].sum = digitSum(i);
			count++;
		}
	}

	if (count == 0) {
		free(result);
		result = NULL;
	}
	else result = (Number*)realloc(result, count * sizeof(Number));

	*p_size = count;
	return result;
}

int** matrixSumNeighbor(int A[][COLS], int rows, int cols)
{
	int** B = allocMatrix(rows, cols);

	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			B[i][j] = neighborSum(A, rows, cols, i, j);
		}
	}
	return B;
}

int createSortedSparseList(int** A, int rows, int cols, Item** lst)
{
	Item* min = NULL;
	Item* max = NULL;
	int count = 0;

	for (int i = 0;i < rows;i++) {
		for(int j=0;j<cols;j++){
			if(A[i][j]!=0){
				Triad t = createThree(i, j, A[i][j]);
				insert(&min, &max, t);
				count++;
			}
		}
	}
	*lst = min;
	return count;
}



/* Definitions of auxiliary functions */

//Question 1 auxiliary functions
void printArray(Number* arr, int size) {
	for (int i = 0;i < size;i++) {
		printf("Number: %d, Digit Sum: %d\n", arr[i].num, arr[i].sum);
	}
}
int isPerfectSquare(int num) {
	int sqrtNum = sqrt(num);
	if (sqrtNum * sqrtNum == num) return 1;
	return 0;
}
int digitSum(unsigned long long num) {
	int sum = 0;
	while (num > 0) {
		sum += num % 10;
		num /= 10;
	}
	return sum;
}


//Question 2 auxiliary functions
int neighborSum(int A[][COLS], int rows, int cols, int i, int j) {
	int sum = 0;

	if (i > 0) sum += A[i - 1][j];           
	if (i < rows - 1) sum += A[i + 1][j];   
	if (j > 0) sum += A[i][j - 1];            
	if (j < cols - 1) sum += A[i][j + 1];    

	return sum;
}
int** allocMatrix(int rows, int cols) {
	int** matrix = (int**)malloc(rows * sizeof(int*));
	assert(matrix);

	for (int i = 0; i < rows; i++) {
		matrix[i] = (int*)malloc(cols * sizeof(int));
		assert(matrix[i]);
	}

	return matrix;
}
void inputMatrix(int A[][COLS], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("Enter Num [%d][%d]: ", i, j);
			scanf("%d", &A[i][j]);
		}
	}
}
void printMatrix(int A[][COLS], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
}
void inputDynamicMatrix(int** A, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("Enter Num [%d][%d]: ", i, j);
			scanf("%d", &A[i][j]);
		}
	}
}
void printDynamicMatrix(int** A, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
}
void freeMatrix(int** A, int rows) {
	int** matrix = A;
	for (int i = 0; i < rows; i++) {
		free(matrix[i]);
	}
	free(matrix);
}


//Question 3 auxiliary functions
Triad createThree(int i, int j, int value) {
	Triad t;
	t.i = i;
	t.j = j;
	t.value = value;
	return t;
}
void insert(Item** min, Item** max, Triad data) {
	Item* newItem = (Item*)malloc(sizeof(Item));
	assert(newItem);
	newItem->data = data;

	if (*min == NULL) { 
		newItem->next = NULL;
		*min = newItem;
		*max = newItem;
		return; 
	}

	if (data.value < (*min)->data.value) { 
		newItem->next = *min;
		*min = newItem;
	}
	else { 
		newItem->next = NULL;
		(*max)->next = newItem;
		*max = newItem;
	}
	
}
void printList(Item* lst){
	while (lst != NULL) {
		printf("i: %d, j: %d, value: %d\n", lst->data.i, lst->data.j, lst->data.value);
		lst = lst->next;
	}
}
void freeList(Item* lst){
	while (lst != NULL) {
		Item* temp = lst;
		lst = lst->next;
		free(temp);
	}
}


/* ------------------- */
