#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "complex.h"

void inputComplex(Complex* c) {
    printf("Enter real and imag:");
    scanf("%lf %lf", &(c->real), &(c->img));
}

void printComplex(Complex c) {
	printf("Complex number: %f + %fi\n", c.real, c.img);
}

Complex sumComplex(Complex n1, Complex n2) {
	Complex n3;
	n3.real = n1.real + n2.real;
	n3.img = n1.img + n2.img;
	return n3;
}

Complex subComplex(Complex n1, Complex n2) {
    Complex n3;
    n3.real = n1.real - n2.real;
    n3.img = n1.img - n2.img;
    return n3;
}

Complex multComplex(Complex n1, Complex n2) {
    Complex n3;
    n3.real = (n1.real * n2.real) - (n1.img * n2.img);
    n3.img = (n1.img * n2.real) + (n1.real * n2.img);

    return n3;
}