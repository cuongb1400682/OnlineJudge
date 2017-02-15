#include <stdio.h>
#include <set>

using namespace std;

typedef pair<int,int> ii;

#define SZ 1024

int ans,n,m,cost[SZ];
set<int> G[SZ];

int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++)
    scanf("%d",&cost[i]);
  for(int i=1;i<=m;i++){
    int u,v;
    scanf("%d%d",&u,&v);
    G[u].insert(v);
    G[v].insert(u);
  }

  ans=0;
  for(int u=1;u<=n;u++){
    for(set<int>::iterator it=G[u].begin();it!=G[u].end();it++)
      ans+=min(cost[u],cost[*it]);
  }
  printf("%d\n",ans/2);
  return 0;
}
