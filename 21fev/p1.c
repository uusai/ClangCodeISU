#include <stdio.h>
#include <math.h>

int main() {
FILE *f1;
f1=fopen("1. dat", "w");
double a = - 10;
double b = 10;
double x, y;
int n = 1000;
for ( int i = 0; i < n; i++) {
    x = a+ (b-a) *i / n;
    y = (sin((1./2. )*M_PI*x))/(1. +pow(M_PI, 2) /100. *fabs (x)) - (log (1. +pow(x, 2)) +M_PI) ;
    fprintf (f1, "%f %f\n", x, y) ;
}
fclose (f1);
return 0;
}
