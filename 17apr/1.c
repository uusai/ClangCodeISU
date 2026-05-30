#include <stdio.h>
#include <math.h>
#define nm 100

double fun (double x) {
    return 1./(1.+2*x*x);
}

double run(int n, double *a, double *b, double *c, double *d, double *y) {
    double v[nm+1], u[nm+1];
    v[1] = -b[1] / a[1];
    u[1] = d[1] / a[1];
    for(int i = 2; i <= n; i++){
        double m = a[i] + c[i] * v[i-1];
        v[i] = -b[i] / m;
        u[i] = (d[i] - c[i] * u[i-1]) / m;
    }
    y[n] = u[n];
    for(int i = n - 1; i >= 1; i--){
        y[i] = v[i] * y[i+1] + u[i];
    }
    return 0;
}

double mix(double z, int i, double *x)
{
	double m = 2, b2ix = 0, xsz,dwixs;
	for (int s = i-1; s<=i+m; s++)
	{
		xsz = (x[s]+x[s-1])*0.5-z;
		if (xsz<0) xsz = 0;
		dwixs = 1;
		for (int j = i-1; j <= i+m; j++)
		{
			if (s!=j)
			{
				dwixs *= (x[s]+x[s-1]-x[j]-x[j-1])*0.5;
			}
		}
		b2ix+=(pow(xsz,m)/dwixs)*3;
	}
	return b2ix*(x[i+2]+x[i+1]-x[i-1]-x[i-2])*0.25;
};

double dmix(double z, int i, double *x)
{
	double m=2, b2ix = 0, xsz,dwixs;
	for (int s = i-1; s<=i+m; s++)
	{
		xsz = (x[s]+x[s-1])*0.5-z;
		if (xsz<0) xsz = 0;
		dwixs = 1;
		for (int j = i-1; j <= i+m; j++)
		{
			if (s!=j)
			{
				dwixs *= (x[s]+x[s-1]-x[j]-x[j-1])*0.5;
			}
		}
		b2ix-=(xsz/dwixs)*6;
	}
	return b2ix*(x[i+2]+x[i+1]-x[i-1]-x[i-2])*0.25;
}

double s2x(double *c, int n, double z, double *x)
{
	double s = 0;
	for (int i = 2; i <= n+3; i++)
	{
		s+=c[i]*(mix(z,i,x));
	}
	return (s);
}

void cirrb (double *x, double *f, double da0, double dbn, double *c,int n)
{
	double da[nm+6], db[nm+6], dc[nm+6], f0, fn;
	for (int i = 1; i<= 3; i++)
	{
		x[3-i]=x[3]-i*(x[4]-x[3]);
		x[n+2+i]=x[n+2]+i*(x[n+2]-x[n+1]);
	}
	for (int i = 4; i <=n+1; i++)
	{
		dc[i]=mix(x[i],i-1,x);
		da[i]=mix(x[i],i,x);
		db[i]=mix(x[i],i+1,x);
	}
	dc[3] = 0;
	da[3]=mix(x[3],3,x)-mix(x[3],2,x)*dmix(x[3],3,x)/dmix(x[3],2,x);
	db[3]=mix(x[3],4,x)-mix(x[3],2,x)*dmix(x[3],4,x)/dmix(x[3],2,x);
	f0=f[3];fn=f[n+2];
	f[3]=f[3]-da0*mix(x[3],2,x)/dmix(x[3],2,x);
	f[n+2]=f[n+2]-dbn*mix(x[n+2],n+3,x)/dmix(x[n+2],n+3,x);
	db[n+2]=0;
	da[n+2]=mix(x[n+2],n+2,x)-mix(x[n+2],n+3,x)*dmix(x[n+2],n+2,x)/dmix(x[n+2],n+3,x);
	dc[n+2]=mix(x[n+2],n+1,x)-mix(x[n+2],n+3,x)*dmix(x[n+2],n+1,x)/dmix(x[n+2],n+3,x);
	run(n, &da[2], &db[2], &dc[2], &f[2],&c[2]);
	c[2] = (da0-dmix(x[3],4,x)*c[4]-dmix(x[3],3,x)*c[3])/dmix(x[3],2,x);
	c[n+3]=(dbn-dmix(x[n+2],n+1,x)*c[n+1]-dmix(x[n+2],n+2,x)*c[n+2])/dmix(x[n+2],n+3,x);
	f[3]=f0; f[n+2]=fn;
	return;
}


int main() {
    // double a[nm+1],b[nm+1], c[nm+1],d[nm+1],y[nm+1];
    // int n, i; n=5;
    // c[1]=0.; a[1]=2.; b[1]=3.; d[1]=5.;
    // c[2]=-1.; a[2]=5.; b[2]=2.; d[2]=-3.;
    // c[3]=17. ; a[3]=2.; b[3]=-1.; d[3]=0.;
    // c[4]=6.; a[4]=0.; b[4]=1.; d[4]=-1.;
    // c[5]=1.; a[5]=1.; b[5]=0.; d[5]=-3.;
    // run(n,a,b, c, d, y);
    // for (i=1; i<=n; i++) printf("y[%d]= %5.2lf\n",i,y[i]);
    // return 0;

    FILE*f1; 
	f1 = fopen("1.dat", "w");
	double x[nm+1], f[nm+1], c[nm+1];
	int n = 13;
	int m = 666;
	double a = -2, b =2, h = (b-a)/(n-1);
	double da0 = -4*a/pow((1+2*pow(a,2)),2);
	double dbn = -4*b/pow((1+2*pow(b,2)),2);
	for (int i = 0; i < n; i++)
	{
		x[i+3]=a+i*h;
		f[i+3]=fun(x[i+3]);
		fprintf(f1,"%lf %lf\n", x[i+3],f[i+3]);
	}
	fclose(f1);
	cirrb(x,f,da0,dbn,c,n);
	f1 = fopen("fun.dat", "w");
	double st = (b-a)/(m-1);
	double z;
	for (int i = 0; i < m; i++)
	{
		z = a+i*st;
		fprintf(f1, "%lf %lf %lf\n", z, fun(z), s2x(c,n,z,x)); 
	}
	fclose(f1);
	return(0);
}
