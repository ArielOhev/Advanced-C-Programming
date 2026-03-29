#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void printArray(int* arr, int size);
void * realloc1( void *memblock, unsigned size_old, unsigned size_new );
int * arrcat( int * arr1, unsigned size1, int * arr2, unsigned size2 );
int *quest3(int *A,int n,int *B,int m,int *Csize);


int main(){
    int *a1 = (int*)malloc(1 * sizeof(int));
    a1[0] = 1;

    int a2[] = {4, 5, 6};
    int *a3 = arrcat(a1, 1, a2, 3);

    printArray(a3, 4);
    free(a3); 

    //quest3

    int A[]={5,7,10,15,2,4};
    int B[]={1,5,2,24,56,70,71};
    int *C,Csize;

    C=quest3(A,6,B,7,&Csize);
    printArray(C,Csize);
    free(C);
    

    return 0;
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

void * realloc1( void *memblock, unsigned size_old, unsigned size_new ){
    void *newMem = malloc(size_new);

    char *src = (char*)memblock;
    char *dest = (char*)newMem;

    unsigned max = (size_old < size_new) ? size_old : size_new;
    for (unsigned i = 0; i < max; i++) {
        dest[i] = src[i];
    }

    free(memblock);
    return newMem;
}

int * arrcat( int * arr1, unsigned size1, int * arr2, unsigned size2 ){
    unsigned newSize=size1+size2;

    int *newA = (int*)realloc1(arr1,size1*sizeof(int),newSize*sizeof(int));
    if(newA==NULL){
        return NULL;
    }    

    int j=0;
    for(int i=size1;i<newSize;i++){
        newA[i]=arr2[j];
        j++;
    }
    return newA;
}

int *quest3(int *A,int n,int *B,int m,int *Csize){
    int *C=(int*)malloc((n+m)*sizeof(int));
    int check,newSize=0;

    for(int i=0;i<n;i++){
        check=1;
        for(int j=0;j<m;j++){
            if(A[i]==B[j]) check=0;
        }
        if(check){
            C[newSize]=A[i];
            newSize++;
        }
    }

    C=realloc1(C,((n+m)*sizeof(int)),newSize*sizeof(int));
    *Csize=newSize;
    return C;
}


