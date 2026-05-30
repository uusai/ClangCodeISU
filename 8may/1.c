#include <stdio.h>
#include <math.h>

FILE *f3_file; 

struct prm{
    double p0,p1,pc,pl;
};

double zerofun(double zx, double zy, struct prm *pm){
    return zy - (pm[0].pc * zx + pm[1].pc);
}

double sums(int n, const double *x, const double *y, const double *w, int np, struct prm *pm, double *lss){
    double s = 0.,zf; int i;
    for(i = 0; i < n; i++){
        zf = zerofun(x[i],y[i],pm);
        s+=pow(zf,2)*w[i];
    }
    return(s);
}

void recyc(int relev, int n, double *x, double *y, double *w, int np, struct prm *pm, int ns, double *lss){
    double st,ss;int i,p;
    if(relev==np) return;
    st=(pm[relev].p1-pm[relev].p0)/(ns-1);
    for(i = 0; i < ns; i++){
        pm[relev].pc=pm[relev].p0+i*st;
        recyc(relev+1,n,x,y,w,np,pm,ns,lss);
        ss=sums(n,x,y,w,np,pm,lss);
        if(ss<(*lss)){
            *lss=ss; 
            for(p=0;p<np;p++) pm[p].pl=pm[p].pc;    
        }
        if (relev == 1 && f3_file != NULL) {
            fprintf(f3_file, "%lf %lf %lf\n", pm[0].pc, pm[1].pc, ss);
        }
    }
    return;
}

void lsm(int n, double *x, double *y, double *w, int np, struct prm *pm, int ns, int ni, double *lss) {
    int itr,p;double st,p0new,p1new;
    for(itr = 0;itr<ni;itr++){
        recyc(0,n,x,y,w,np,pm,ns,lss);
        for(p=0;p<np;p++){
            st=(pm[p].p1-pm[p].p0)/(ns-1);
            p0new=pm[p].pl-st; if (p0new<pm[p].p0) p0new=pm[p].p0;
            p1new=pm[p].pl+st; if (p1new>pm[p].p1) p1new=pm[p].p1;
            pm[p].p0=p0new; pm[p].p1=p1new;
        }
    }
    return;
}
double k(const double *x, const double *y, int n){
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0;
    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }
    double numerator = (double)n * sum_xy - sum_x * sum_y;
    double denominator = (double)n * sum_x2 - sum_x * sum_x;
    if (denominator == 0) return 0;
    return numerator / denominator;
}

double b(const double *x, const double *y, int n, double k) {
    double sum_x = 0.0,sum_y = 0.0;
    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
    }
    return (sum_y - k * sum_x) / (double)n;
}


int main(){
    FILE *file = fopen("file1.dat", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return 1;
    }
    int n = 1000;
    double w[n];
    double x[n],y[n];

    int i = 0;
    while (fscanf(file, "%lf %lf", &x[i], &y[i]) == 2) {
        w[i] = 1.0;
        i++;
    }
    fclose(file);
    struct prm pm[2];
    pm[0].p0=-0.6; pm[0].p1=-0.2;
    pm[1].p0= 2.0; pm[1].p1= 4.0;
    int np = 2, ns = 100, ni = 5;
    double lss = 1e308;
    f3_file = fopen("f3.dat", "w");
    if (f3_file == NULL) {
        printf("Ошибка создания f3.dat\n");
        return 1;
    }
    lsm(n,x,y,w,np,pm,ns,ni,&lss);
    printf("lss=%f\n",lss);
    for (i=0; i<np; i++) printf("pm[%d].pl=%lf\n", i,pm[i].pl);
    fclose(f3_file);

    //printf("%lf %lf\n",k(x,y,n),b(x,y,n,k(x,y,n)));
    return 0;


}