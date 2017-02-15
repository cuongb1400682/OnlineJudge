#include <stdio.h>

long long deg[1000005],n,m,sum;

int main(){
  scanf("%I64d%I64d",&n,&m);
  for(long long i=1;i<=m;i++){
    long long u,v;
    scanf("%I64d%I64d",&u,&v);
    deg[u]++,deg[v]++;
  }
  sum=0;
  for(long long u=1;u<=n;u++){
    long long e=deg[u],a=(n-1)-deg[u];
    sum+=e*(e-1)+a*(a-1)-a*e;
  }
  printf("%I64d\n",sum/6);
  return 0;
}
