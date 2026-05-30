#include <stdio.h>
#include <math.h>

double fun8(double x){
    return exp(x);
}

double fun7(double x){
    return 1./sqrt(sin(x)+atan(x));
}

double fun6(double x){
    return 1./sqrt(sin(x));
}

double fun5(double x){
    return (exp(2.*x)/(1.+exp(x)));
}

double fun4(double x){
    return (exp(pow(-x,2.)));
}

double fun3(double x){
    return (sin(5.*M_PI*x)*cos(M_PI*x)+1.);
}

double fun2(double x){
    return (1./(1.+sqrt(x)));
}

double fun1(double x){
    return ((3. * (x*x))+(2.*x)+1.);
}

double integrate_rect(double (*fun)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += fun(a + h * (i + 0.5));
    }
    return sum * h;
}

double integrate_trap(double (*fun)(double), double a, double b, int n){
    double h = (b - a) / n;
    double sum = (fun(a) + fun(b)) / 2.0;

    for (int i = 1; i < n; i++) {
        sum += fun(a + h * i);
    }
    return sum * h;
}

double integrate_simp(double (*fun)(double), double a, double b, int n){
    n*=2;
    double h = (b - a) / n;
    double sum = fun(a) + fun(b);
    for(int i = 1; i < n; i++){
        double x = a + i * h;
        sum+=(i % 2 == 0) ? 2. * fun(x) : 4. * fun(x); 
    }
    return sum * h / 3.;
    //return (1./3. * integrate_trap(a,b,n) + 2./3. * integrate_rect(a,b,n));
}

double r(double a, double b, int n){
    double h = (b-a)/n;
    double s = 0.;
    for(int i = 0; i<n; i++) s+=fun6(a+h*(i+0.5));
    return (h*s);
}
double t(double a, double b, int n){
    double h = (b-a)/n;
    double s = (fun7(a)+fun7(b))*0.5;
    for(int i = 0; i<n;i++){
        s+=fun7(a+i*h);
    }
    return(h*s);
}


int main(){
    double eps = 0.01;
    double ai = 0;//sqrt(2. * eps);
    double a = -200.;
    double b = 0.;
    int n = 1000;
    printf("%f", ai + integrate_rect(fun8, a,b,n));
    printf("\n");
    printf("%f", ai +integrate_trap(fun8, a,b,n));
    printf("\n");
    printf("%f", ai + integrate_simp(fun8, a,b,n));
    printf("\n");
    //printf("%f", r(a,b,n));
    printf("\n");
    //printf("%f", t(a,b,n));
}
