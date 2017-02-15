#include <stdio.h>
#include <string.h>
#include <set>

using namespace std;

#define SZ 50005

int parent[SZ],n,r1,r2,v;
set<int> G[SZ];

void dfs(int u,int *parent){
  for(set<int>::iterator it=G[u].begin();it!=G[u].end();it++){
    if(parent[*it]==0){
      parent[*it]=u;
      dfs(*it,parent);
    }
  }
}

int main(){
  scanf("%d%d%d",&n,&r1,&r2);
  for(int u=1;u<=n;u++){
    if(u==r1)
      continue;
    scanf("%d",&v);
    G[u].insert(v);
    G[v].insert(u);
  }
  memset(parent,0,sizeof(parent));
  parent[r2]=r2;
  dfs(r2,parent);
  for(int u=1;u<=n;u++)
    if(u!=r2)
      printf("%d ",parent[u]);
  printf("\n");
  return 0;
}
