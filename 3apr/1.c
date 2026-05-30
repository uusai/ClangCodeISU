#include <stdio.h>
#include <math.h>

double b2j(double*x, int i, double z){
    double b2jx=0;
    double xsx,dwixs;
	for(int s=i-1;s<=i+2;s++){
		xsx = 0.5*(x[s-1]+x[s])-z;
		dwixs = 1.0;
		for(int j=i-1;j<=i+2;j++){
			if(s!=j) dwixs*=(x[s-1]+x[s]-x[j-1]-x[j])*0.5;
        }
		if(xsx>0) b2jx+=pow(xsx,2)/dwixs;
    }
	return (3.*b2jx);
	
}
	
int main(){
    double mx[10]={1,2,3,4,5,6,7,8,9,10};
    double z; FILE*f;
    f = fopen("xy.dat","w");
    double eps = 0.01;
    double a = 0.;
    double b = 10.;
    for(z=a;z<b;z+=eps){
    	fprintf(f, "%lf %lf %lf %lf %lf\n", z, b2j(mx, 2, z), b2j(mx, 3, z), b2j(mx, 4, z), b2j(mx,5,z));
    }
    return(0);
}