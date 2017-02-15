#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define N 10005

bool on_stk[N],vis[N];
int low[N],num[N],parent[N],root,deg,ans,n,m,n_lab;
vector<int> G[N];

void dfs(int u){
  on_stk[u]=true;
  low[u]=num[u]=++n_lab;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(num[v]==0){
      parent[v]=u;
      dfs(v);
      if(u==root)
        deg++;
      else if(low[v]>=num[u]&&!vis[u])
        ans++,vis[u]=true;
      low[u]=min(low[u],low[v]);
    }else if(on_stk[v]&&parent[u]!=v){
      low[u]=min(low[u],num[v]);
    }
  }
  on_stk[u]=false;
}

void init(){
  memset(low,0,sizeof(low));
  memset(num,0,sizeof(num));
  memset(parent,0,sizeof(parent));
  memset(on_stk,0,sizeof(on_stk));
  memset(vis,0,sizeof(vis));
  for(int u=1;u<=n;u++)
    G[u].clear();
  n_lab=0;
}

int main(){
  int no=0,T;
  scanf("%d",&T);
  while(T--){
    scanf("%d%d",&n,&m);

    init();
    
    for(int i=1;i<=m;i++){
      int u,v;
      scanf("%d%d",&u,&v);
      G[u].push_back(v);
      G[v].push_back(u);
    }

    ans=0;
    for(int u=1;u<=n;u++)
      if(num[u]==0){
        root=u;
        deg=0;
        dfs(u);
        if(deg>1)
          ans++;
      }
    printf("Case %d: %d\n",++no,ans);
  }
  return 0;
}
