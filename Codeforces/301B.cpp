#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <set>

using namespace std;

typedef pair<int,int> ii;

#define SZ 128

int w[SZ][SZ],d,n,a[SZ];
ii pt[SZ];

int weight(ii a,ii b){
  return d*(abs(a.first-b.first)+abs(a.second-b.second));
}

int main(){
  scanf("%d%d",&n,&d);
  for(int i=2;i<=n-1;i++)
    scanf("%d",&a[i]);
  for(int i=1;i<=n;i++)
    scanf("%d%d",&pt[i].first,&pt[i].second);
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++)
      w[i][j]=weight(pt[i],pt[j])-a[i];
    w[i][i]=1000000000;
  }
      

  for(int k=1;k<=n;k++)
    for(int u=1;u<=n;u++)
      for(int v=1;v<=n;v++)
        w[u][v]=min(w[u][v],w[u][k]+w[k][v]);

  printf("%d\n",w[1][n]);
  return 0;
}
