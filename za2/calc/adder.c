#include <stdio.h>

double add(double a, double b){
    fprintf(stderr, "input = %f, %f\n", a, b);
    return a + b;
}

