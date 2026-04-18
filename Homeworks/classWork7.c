#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>

#define COL 3
#define ROW 3

void printMat(int** mat);
void swapRows(int** mat, int row1, int row2);
void swapCols(int** mat, int rows, int col1, int col2);

int main()
{
	int mat[ROW][COL] = { {1,2,3},{4,5,6},{7,8,9} };
	int* ptrs[ROW] = { mat[0], mat[1], mat[2] };

	printMat(ptrs);
	swapRows(ptrs, 0, 2);
	printf("\n");
	printf("After swapping rows 0 and 2:\n");
	printMat(ptrs);




	swapCols(ptrs, ROW, 1, 2);
	printf("\n");
	printf("After swapping columns 1 and 2:\n");
	printMat(ptrs);

	

	
	return 0;
}

void printMat(int** mat) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

void swapRows(int** mat, int row1, int row2) {
	int* temp = mat[row1];
	mat[row1] = mat[row2];
	mat[row2] = temp;
}

void swapCols(int **mat,int rows,int col1,int col2){
	int temp;
	for (int i = 0; i < rows; i++) {
		temp= mat[i][col1];
		mat[i][col1] = mat[i][col2];
		mat[i][col2] = temp;
	}

}








