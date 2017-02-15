#include<stdio.h>
#include<math.h>

int main(){
    int n=10000;
    double a,b,c,d;
    while(scanf("%lf%lf%lf%lf",&a,&b,&c,&d)!=EOF){
        double p=(1.0-a/b)*(1-c/d);
        printf("%.12lf\n",(a/b)*(1-pow(p,n))/(1-p));        
    }
    return 0;
}
