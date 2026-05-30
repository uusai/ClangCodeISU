#include <stdio.h>
#include <math.h>

int main(){
    FILE*f;
    double a,b,st,x,y;
    int i,n;
    f = fopen("01sqrt.dat","w");
    a = -1.; b = 1.;n=101;
    st = (b-a)/(n-1); x = a - st;
    for(i=0;i<n;i++){
        x+=st; 
        y = sin(2*M_PI*x);
        fprintf(f,"%lf %lf\n",x,y);
    }
    fclose(f);
    return(0);
}