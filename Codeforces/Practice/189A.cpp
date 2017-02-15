#include <stdio.h>

#define N 4005

int a,b,c,n,x[N];

int max(int a,int b){
  return a>b?a:b;
}

int main(){
  scanf("%d%d%d%d",&n,&a,&b,&c);
  x[a]=x[b]=x[c]=1;
  for(int i=1;i<=n;i++){
    if(x[i]>0){
      if(i+a<=n)x[i+a]=max(x[i+a],x[i]+1);
      if(i+b<=n)x[i+b]=max(x[i+b],x[i]+1);
      if(i+c<=n)x[i+c]=max(x[i+c],x[i]+1);
    }
  }
  printf("%d\n",x[n]);
  return 0;
}
