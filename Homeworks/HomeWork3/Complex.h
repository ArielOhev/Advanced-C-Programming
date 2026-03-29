#ifndef COMPLEX_H 

typedef struct complex {
    double real;
    double img;
} Complex;

void inputComplex(Complex* c);
void printComplex(Complex c);
Complex sumComplex(Complex n1, Complex n2);
Complex subComplex(Complex n1, Complex n2);

#endif