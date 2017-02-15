#include<stdio.h>

int max(int a,int b){return a>b?a:b;}
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}

int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    int m=max(a,b);
    int g=gcd(6-m+1,6);
    printf("%d/%d\n",(6-m+1)/g,6/g);
    return 0;
}
