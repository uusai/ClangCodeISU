#include <stdio.h>
#include <math.h>
double fun(double x) {return ((atan(x))/(1+x));};
double bs(double a,double b,double eps) 
{int n = 0; double c; 
	do {c=(b+a)/2;
		 if (fun(a)*fun(c)<=0) b = c;
		  else {a = c; n++;}} 
		  while (fabs(b-a)>eps); 
		  printf("bs: число итераций n = %d\n", n); 
		  return ((b+a)/2);};
double ms(double x1, double x2, double eps){
	int n = 0;
	double x0,e0,la,y1,y2;
	y1=fun(x1); y2=fun(x2); la=(x2-x1)/(y2-y1);
	x0=(y2*x1-y1*x2)/(y2-y1);
	do { e0=la*fun(x0); x0-=e0; n++;}
	while(fabs(e0)>eps);
	printf("ms: число итераций n = %d\n", n);
	return (x0);}
double fr(double a, double b, double eps) {
	int n = 0;
	while (fabs(b-a)>eps){ n+=2;
		a=b-(b-a)*fun(b)/(fun(b)-fun(a));
		b=a-(b-a)*fun(a)/(fun(a)-fun(b));
	}
	printf("fr: число итераций n = %d\n", n);
	return b;
}
int main(){FILE *f1; 
	f1=fopen("23.dat", "w");
	double a=-3, b=3, st, x, y; int n=401; double eps = 0.0001;
	st=(b-a)/(n-1); x=a-st;
	for (int i=0; i<n; i++){ x+=st;
		y=fun(x);
		fprintf(f1, "%f %f\n", x,y);}
		fclose(f1);
	printf("bs x =%lf\n",bs(a,b,eps));
	printf("ms x =%lf\n",ms(a,b,eps));
	printf("fr x =%lf\n",fr(a,b,eps));
	return (0);}
