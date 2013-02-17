#include <stdio.h>

double div(double a, double b){
    if(b == 0){
        fprintf(stderr, "div zero error\n");
        return -1;
    }else{
        return a / b;
    }
}
