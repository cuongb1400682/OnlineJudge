#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define N 10005

struct Edge{
  int u,v;
  bool is_erased;
  Edge(int u=0,int v=0,bool is_erased=false):
    u(u),v(v),is_erased(is_erased){}
};

vector<Edge> e;
vector<int> G[N];
int T,n,m,num[N],low[N],n_lab,parent[N],sz,ans,color[N];
bool on_stk[N],has_odd_circle;

void dfs(int u){
  num[u]=low[u]=++n_lab;
  on_stk[u]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=(e[G[u][i]].u==u?e[G[u][i]].v:e[G[u][i]].u);
    if(num[v]==0){
      parent[v]=u;
      dfs(v);
      if(low[v]>num[u])
        e[G[u][i]].is_erased=true;
      low[u]=min(low[u],low[v]);
    }else if(on_stk[v]&&parent[u]!=v){
      low[u]=min(low[u],num[v]);
    }
  }
  on_stk[u]=false;
}

void dfs2(int u,int &sz){
  sz++;
  for(int i=0;i<(int)G[u].size();i++){
    int v=(e[G[u][i]].u==u?e[G[u][i]].v:e[G[u][i]].u);
    if(e[G[u][i]].is_erased){
      continue;
    }    
    if(color[v]==0){
      color[v]=-color[u];
      dfs2(v,sz);
    }else if(color[v]==color[u]){
      has_odd_circle=true;
    }
  }
}

void init(){
  e.clear();
  for(int u=0;u<n;u++){
    G[u].clear();
    num[u]=low[u]=0;
    parent[u]=0;
    on_stk[u]=false;
    color[u]=0;
  }
  n_lab=0;
  ans=0;
}

int main(){
  scanf("%d",&T);
  int no=0;
  while(T--){
    scanf("%d%d",&n,&m);

    init();
    
    e.assign(m,Edge());
    for(int i=0;i<m;i++){
      scanf("%d%d",&e[i].u,&e[i].v);
      G[e[i].u].push_back(i);
      G[e[i].v].push_back(i);
    }

    for(int u=0;u<n;u++)
      if(num[u]==0)
        dfs(u);

    for(int u=0;u<n;u++)
      if(color[u]==0){
        has_odd_circle=false;
        sz=0;
        color[u]=1;
        dfs2(u,sz);
        if(has_odd_circle)
          ans+=sz;
      }

    printf("Case %d: %d\n",++no,ans);
  }
  return 0;
}

