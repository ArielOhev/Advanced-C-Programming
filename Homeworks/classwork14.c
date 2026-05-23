#include <stdio.h>
#include <string.h>

typedef union {
    char ch;
    int num;
	double dnum;
} type;

typedef struct {
	int type;
    type data;
} three_type;


void quest1a(int type, three_type* t);
void quest1b(three_type t);
void quest2();


int main() {
    three_type myVar;

    quest1a(2, &myVar);
    quest1b(myVar);

    printf("\nTesting quest2 (calling 6 times):\n");
    for (int i = 0; i < 6; i++) {
        quest2();
    }
    return 0;
}

void quest1a(int type, three_type* t) {
    char ch;

    switch (type) {

    case 1:
        t->type = 1;
        printf("Type: char\n");
        scanf("%c", &t->data.ch);
        break;

    case 2:
        t->type = 2;
        printf("Type: int\n");
        scanf("%d", &t->data.num);
        break;

    case 3:
        t->type = 3;
        printf("Type: double\n");
        scanf("%lf", &t->data.dnum);
        break;
    }
}

void quest1b(three_type t) {

    switch (t.type) {
    case 1:
        printf("Type: char %c\n",t.data.ch);
        break;

    case 2:
        printf("Type: int %d\n", t.data.num);
        break;

    case 3:
        printf("Type: double %lf\n", t.data.dnum);
		break;
    }

   


    
}

void quest2() {
    static int num=0;
    num++;
    if (num % 3 == 0) {
        printf("third time lucky\n");
    }
}