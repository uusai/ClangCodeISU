#include <stdio.h>
#include <math.h>

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

double fun(double x){
    return (x/sqrt(pow(x,4.)+16.));
}

double integrate_rect(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += fun3(a + h * (i + 0.5));
    }
    return sum * h;
}

double integrate_trap(double a, double b, int n){
    double h = (b - a) / n;
    double sum = (fun3(a) + fun3(b)) / 2.0;

    for (int i = 1; i < n; i++) {
        sum += fun3(a + h * i);
    }
    return sum * h;
}

double integrate_simp(double a, double b, int n){
    n*=2;
    double h = (b - a) / n;
    double sum = fun3(a) + fun3(b);
    for(int i = 1; i < n; i++){
        double x = a + i * h;
        sum+=(i % 2 == 0) ? 2. * fun3(x) : 4. * fun3(x); 
    }
    return sum * h / 3.;
    //return (1./3. * integrate_trap(a,b,n) + 2./3. * integrate_rect(a,b,n));
}

double r(double a, double b, int n){
    double h = (b-a)/n;
    double s = 0.;
    for(int i = 0; i<n; i++) s+=fun3(a+h*(i+0.5));
    return (h*s);
}
double t(double a, double b, int n){
    double h = (b-a)/n;
    double s = (fun3(a)+fun3(b))*0.5;
    for(int i = 0; i<n;i++){
        s+=fun3(a+i*h);
    }
    return(h*s);
}


int main(){
    double a = 0.;
    double b = 99.5;
    int n = 1000;
    printf("%f", integrate_rect(a,b,n));
    printf("\n");
    printf("%f", integrate_trap(a,b,n));
    printf("\n");
    printf("%f", integrate_simp(a,b,n));
    printf("\n");
    printf("%f", r(a,b,n));
    printf("\n");
    printf("%f", t(a,b,n));
}
