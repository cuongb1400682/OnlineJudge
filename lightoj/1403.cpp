#include<stdio.h>
#include<string.h>
#include<list>
using namespace std;

#define N 1005

int p[N],n,m;
bool vis[N];
list<int> G[N];

int dfs(int u){
  if(vis[u])return 0;
  vis[u]=true;
  for(list<int>::iterator it=G[u].begin();it!=G[u].end();it++)
    if(p[*it]==-1||dfs(p[*it])){
      p[*it]=u;
      return 1;
    }
  return 0;
}

int hopcroft_karp(){
  int ans=0;
  memset(p,-1,sizeof(p));
  for(int u=1;u<=n;u++){
    memset(vis,0,sizeof(vis));
    ans+=dfs(u);
  }
  return ans;
}

int main(){
  int ncase,no=0;
  scanf("%d",&ncase);
  while(ncase--){
    scanf("%d%d",&n,&m);
    for(int u=1;u<=n;u++)
      G[u].clear();
    for(int i=1;i<=m;i++){
      int u,v;
      scanf("%d%d",&u,&v);
      G[u].push_back(v);
    }
    printf("Case %d: %d\n",++no,n-hopcroft_karp());
  }
  return 0;
}
