#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printString(char* str);
void printArray(int* arr, int size);
int *quest1(int *arr,int size ,int** oddArray, int* evenSize, int* oddSize);
void splitChars(char* A, int sizeA, char** upperArr, int* upperSize, char** lowerArr, int* lowerSize);
int RemoveDupV2(int *A, int size, int **newA);
int *RemoveDupV1(int *A,int size,int *newsize);
void RemoveDupV3(int *A, int size, int **newA, int *newsize);

int main(){
    int originalArr[] = {50, 60, 60, 72, 81, 81, 81, 81, 93, 93};
    int size = 10;
    int newSize = 0;

    int* cleanArr = RemoveDupV1(originalArr, size, &newSize);

    printArray(originalArr, size);


    printArray(cleanArr, newSize);
    free(cleanArr);


    return 0;
}

void printString(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", str[i]);
    }
    printf("\n"); 
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

int *quest1(int *arr,int size ,int** oddArray, int* evenSize, int* oddSize){
    int* evens = (int*)malloc(size * sizeof(int));
    int* odds = (int*)malloc(size * sizeof(int));

    int eCount = 0, oCount = 0;
    for(int i = 0; i < size; i++) {
        if(arr[i] % 2 == 0) evens[eCount++] = arr[i];
        else odds[oCount++] = arr[i];
    }

    evens = (int*)realloc(evens, eCount * sizeof(int));
    *oddArray = (int*)realloc(odds, oCount * sizeof(int));

    *evenSize = eCount;
    *oddSize = oCount;

    return evens;


}

void splitString(char* A, int sizeA, char** upperArr, int* upperSize, char** lowerArr, int* lowerSize){ 
    char* BigLetters = (char*)malloc(sizeA * sizeof(char));
    char* SmallLetters = (char*)malloc(sizeA * sizeof(char));

    int Bletter=0,Sletter=0;

    for(int i=0;i<sizeA;i++){
        if(A[i] >= 'a' && A[i] <= 'z'){
            SmallLetters[Sletter]=A[i];
            Sletter++;
        }
        else{
            BigLetters[Bletter]=A[i];
            Bletter++;
        }
    }

    BigLetters = (char*)realloc(BigLetters, (Bletter + 1) * sizeof(char));
    BigLetters[Bletter] = '\0'; 

    SmallLetters = (char*)realloc(SmallLetters, (Sletter + 1) * sizeof(char));
    SmallLetters[Sletter] = '\0';

    *upperSize=Bletter;
    *lowerSize=Sletter;

    *upperArr=BigLetters;
    *lowerArr=SmallLetters;
}

void splitChars(char* A, int sizeA, char** upperArr, int* upperSize, char** lowerArr, int* lowerSize) { 
    char* BigLetters = (char*)malloc(sizeA * sizeof(char));
    char* SmallLetters = (char*)malloc(sizeA * sizeof(char));

    int Bletter = 0, Sletter = 0;

    for (int i = 0; i < sizeA; i++) {
        if (A[i] >= 'a' && A[i] <= 'z') {
            SmallLetters[Sletter] = A[i];
            Sletter++;
        }
        else { 
            BigLetters[Bletter] = A[i];
            Bletter++;
        }
    }

    BigLetters = (char*)realloc(BigLetters, Bletter * sizeof(char));
    SmallLetters = (char*)realloc(SmallLetters, Sletter * sizeof(char));

    *upperSize = Bletter;
    *lowerSize = Sletter;

    *upperArr = BigLetters;
    *lowerArr = SmallLetters;
}

int *RemoveDupV1(int *A,int size,int *newsize){
    int *NewA=(int*)malloc(size*sizeof(int));
    int newAsize=0;

    for (int i = 0; i < size; i++) {
        if (i == size - 1 || A[i] != A[i + 1]) {
            NewA[newAsize]=A[i];
            newAsize++;
        }
    }
    
    NewA=(int*)realloc(NewA,newAsize*sizeof(int));
    *newsize=newAsize;
    return NewA;
}

int RemoveDupV2(int *A, int size, int **newA) {
    int *NewA = (int*)malloc(size * sizeof(int));

    int newAsize = 0;

    for (int i = 0; i < size; i++) {
        if (i == size - 1 || A[i] != A[i + 1]) {
            NewA[newAsize] = A[i];
            newAsize++;
        }
    }

    NewA = (int*)realloc(NewA, newAsize * sizeof(int));
    
    *newA = NewA; 
    
    return newAsize;
}

void RemoveDupV3(int *A, int size, int **newA, int *newsize) {
    int *NewA = (int*)malloc(size * sizeof(int));

    int newAsize = 0;

    for (int i = 0; i < size; i++) {
        if (i == size - 1 || A[i] != A[i + 1]) {
            NewA[newAsize] = A[i];
            newAsize++;
        }
    }

    NewA = (int*)realloc(NewA, newAsize * sizeof(int));

    *newA = NewA;
    *newsize = newAsize;
}



