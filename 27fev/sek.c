#include <stdio.h>
#include <math.h>

double f(double x) {
    return (x*log(fabs(x)));
}

double ms(double x1, double x2, double eps) {
    double x0, e0, la, y1, y2;
    y1=f(x1); y2=f(x2); la=(x2-x1)/(y2-y1);
    x0=(y2*x1-y1*x2)/(y2-y1);
    do { 
        e0=la*f(x0); 
        x0-=e0; 
    }
    while (fabs (e0)>eps);
    return (x0);
}
double fr(double a, double b, double eps){
    int n=0.;
    while(fabs(b-a)>eps){
        n+=2.;
        a=b-(b-a)*f(b)/(f(b)-f(a));
        b=a-(a-b)*f(a)/(f(a)-f(b));
    }
    return b;
}
double bs(double a, double b, double eps){
    int n=0;double c;
    do {
        c = (b+a)/2.;
        if(f(a)*f(c)<=0.) b = c; else a = c;
        n++;
    }
    while(fabs(b-a)>eps);
    printf("bs: Number iteration n=%d\n",n);
    return((b+a)/2.);
}


int main(){
    FILE *f1;
    f1=fopen("23.dat", "w");
	double a=-3, b=3, st, x, y; int n=401; double eps = 0.0001;
	st=(b-a)/(n-1); x=a-st;
	for (int i=0; i<n; i++){ x+=st;
		y=f(x);
		fprintf(f1, "%f %f\n", x,y);}
		fclose(f1);
	printf("bs x =%lf\n",bs(a,b,eps));
	printf("ms x =%lf\n",ms(a,b,eps));
	printf("fr x =%lf\n",fr(a,b,eps));
    printf("f(0) =%lf\n",f(x));
}