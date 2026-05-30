#include <stdio.h>
#include <math.h>

double f(double x){
    return fabs(x);
}

double df(double x, double h){
    return();
}

int main() {
FILE *f1;
f1=fopen("1.dat", "w");
double a = -10.;
double b = 10.;
double x, y;
int n = 1000;
for ( int i = 0; i < n; i++) {
    x = a+(b-a) *i / n;
    y = f(x);
    fprintf(f1, "%f %f\n", x, y) ;
}
fclose (f1);
return 0;
}