#include<stdio.h>
#include<string.h>

#define N 128
#define INF 0x3f3f3f3f

int n,m,a[N][N],nTest,no;

int min(int a,int b){
  return a>b?b:a;
}

int main(){
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d%d",&n,&m);
    memset(a,0x3f,sizeof(a));
    for(int i=1;i<=m;i++){
      int u,v,w;
      scanf("%d%d%d",&u,&v,&w);
      a[u][v]=min(a[u][v],w);
      a[v][u]=min(a[v][u],w);
    }
    for(int u=1;u<=n;u++)a[u][u]=0;
    for(int k=1;k<=n;k++)
      for(int u=1;u<=n;u++){
        if(a[u][k]>=INF)continue;
        for(int v=1;v<=n;v++)
          if(a[k][v]<INF&&a[u][k]+a[k][v]<a[u][v])
            a[u][v]=a[u][k]+a[k][v];
      }
    printf("Case %d: ",++no);
    if(a[1][n]==INF)
      puts("Impossible");
    else
      printf("%d\n",a[1][n]);
  }
  return 0;
}
