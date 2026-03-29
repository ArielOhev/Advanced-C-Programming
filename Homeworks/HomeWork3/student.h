#ifndef STUDENT_H

typedef struct student {
    char name[30];
    int id_card;
    int grade;
} student;

void printStudent(student s);
int countAvg(student* A, int size, int* avg);

#endif