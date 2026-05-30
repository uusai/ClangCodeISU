#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f0(double t){
    if(t == 0) return 1.;
    return(sin(t)/t);
}

double f1(double t, double dt, int n, double *a, double *b){
    int k; double s,i = t/dt;
    s=a[0];
    for(k=1;k<=n/2;k++) s+=a[k]*cos(2.*M_PI*k*i/n)+b[k]*sin(2.*M_PI*k*i/n);
    return s;
}

void akbk(int n, double *x, double *a, double *b){
    int k,i;
    for(k=0;k<=n/2;k++){
        a[k]=0.; b[k]=0.;
        for(i=0; i<n; i++){
            a[k]+=x[i]*cos(2.*M_PI*i*k/n);
            b[k]+=x[i]*sin(2.*M_PI*i*k/n);
        }
        a[k]*=2./n; b[k]*=2./n;
    }
    a[0]/=2.; a[n/2]/=2.;
    return;
}

int main(){
    const int n = 32;    
    const double dt = 0.5;
    const double T = n * dt;
    const double dw = 1.0 / T;
    double t, Ew,Et,*a,*b,*x;
    FILE* f; int i,k,j=n/2+1;
    
    x = malloc(sizeof(double) * n);
    for(i = 0; i < n; i++) {
        if (i == 16) {
            x[i] = 1.0;
        } 
        else {
            x[i] = 0.0;
        }
    }
    a=malloc(sizeof(double)*j); b=malloc(sizeof(double)*j);
    akbk(n,x,a,b);
    printf("df: %.2f Гц\n", dw);
    printf("MaxHz: %.2f Гц\n", 1.0 / (2.0 * dt));
    Et = 0.; for(i=0;i<n;i++) Et+=x[i]*x[i]; Et*=dt;
    Ew = 0.; for(k=0;k<=n/2;k++) Ew+=0.5*(a[k]*a[k]+b[k]*b[k]); Ew/=dw;
    printf("Et: %f\n", Et);
    printf("Ew: %f\n", Ew);
    f = fopen("11.dat", "w");
    for(t = 0; t <= T; t += T / 500.0) {
        fprintf(f, "%e %e %e\n", t, f0(t), f1(t, dt, n, a, b));
    }
    fclose(f);

    f = fopen("22.dat", "w");
    for(i = 0; i < n; i++) {
        fprintf(f, "%e %e\n", i * dt, x[i]);
    }
    fclose(f);

    f = fopen("33.dat", "w");
    for(k = 0; k <= n / 2; k++) {
        double pk = 0.5*(a[k]*a[k] + b[k]*b[k]);
        fprintf(f, "%e %e %e %e\n", k * dw, a[k], b[k], pk);
    }
    fclose(f);

    free(x); free(a); free(b);
    return 0;
}

/*
 График сигнала 
 plot "11.dat" u 1:2 w l title "Исходный", "11.dat" u 1:3 w l dt 2 title "Восстановленный", "22.dat" u 1:2 w p pt 7 ps 1.5 title "Отсчеты"

 График спектра
 plot "33.dat" u 1:2 w lp title "a[k]", "33.dat" u 1:3 w lp title "b[k]", "33.dat" u 1:4 w lp title "p[k]"
*/