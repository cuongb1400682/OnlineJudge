#include <stdio.h>

bool G[128][128];
int n,x[128];

int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
    scanf("%d",&x[i]);
  for(int u=1;u<=n;u++){
    G[u][u]=true;
    int v;
    scanf("%d",&v);
    if(u-v>0&&u-v<=n){
      G[u][u-v]=true;
      G[u-v][u]=true;
    }
    if(u+v<=n){
      G[u][u+v]=true;
      G[u+v][u]=true;
    }
  }

  for(int k=1;k<=n;k++)
    for(int u=1;u<=n;u++)
      for(int v=1;v<=n;v++){
        G[u][v]=G[u][v]||(G[u][k]&&G[k][v]);
      }
  
  for(int u=1;u<=n;u++)
    if(!G[u][x[u]]){
      puts("NO");
      return 0;
    }
  puts("YES");
  return 0;
}
