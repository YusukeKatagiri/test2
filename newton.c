#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max 1000
#define eps 1.0e-5

double f(double x);
double df(double x);
double ddf(double x);
void newton(void);

int main()
{
	newton();

	FILE *gp;
	gp=popen("/usr/local/bin/gnuplot -persist","w");

	fprintf(gp, "set title 'df(x)=-1/x^2+1/x'\n");
	fprintf(gp, "set size ratio 1.0\n");
	fprintf(gp, "set border lw 2.5\n");
	fprintf(gp, "set mxtics 5\n");
	fprintf(gp, "set mytics 5\n");
	fprintf(gp, "set nokey\n");
	fprintf(gp, "set xl 'x' font 'Arial'\n");
	fprintf(gp, "set yl 'df(x)' font 'Arial'\n");
	fprintf(gp, "set parametric\n");
	fprintf(gp, "const=0\n");
	fprintf(gp, "set trange[-5:5]\n");
	fprintf(gp, "set xr [0:5]\n");
	fprintf(gp, "set yr [-5:1]\n");
	fprintf(gp, "plot const+1.5,t dt(10,5) lw 2.5 lt 1 lc rgb 'black'\n");
	fprintf(gp, "replot t,const dt(5,5) lw 2.5 lt 1 lc rgb 'black'\n");
	fprintf(gp, "replot t,t*4/27 dt(5,5) lw 2.5 lt 1 lc rgb 'navy'\n");
	fprintf(gp, "replot t,-1/(t*t)+1/t  w l lw 3 lt 1 lc rgb 'red'\n");

	pclose(gp);

        return 0;
}

void newton(void)
{
        int count;
        double a,newa,fx;

        count=0;

        printf("初期を入力\n");
        scanf("%lf",&a);

        for(;;) {
                count++;

                newa=a-df(a)/ddf(a);

                if(fabs(newa-a) < eps) break;

                a=newa;

                if(count==max) {
                        printf("収束せず\n");
                        exit(1);
                }
        }
        printf("最小値は%f\n収束まで%d回\n", f(newa),count);
}


double f(double x)
{
        return (1.0/x)+log(x);
}

double df(double x)
{
        return 1.0/x-1.0/(x*x);
}
double ddf(double x)
{
        return 2.0/(x*x*x)-1.0/(x*x);
}

