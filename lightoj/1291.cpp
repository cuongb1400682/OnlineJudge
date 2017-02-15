#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

#define N 10005

typedef pair<int,int> ii;

int num[N],low[N],parent[N],p[N],lab[N],deg[N],n_lab,n,m;
bool on_stk[N];
vector<ii> e;
vector<int> G[N];

void dfs(int u){
  num[u]=low[u]=++n_lab;
  on_stk[u]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(num[v]==0){
      parent[v]=u;
      dfs(v);
      if(low[v]>num[u])
        e.push_back(u<v?ii(u,v):ii(v,u));
      low[u]=min(low[u],low[v]);
    }else if(on_stk[v]&&parent[u]!=v){
      low[u]=min(low[u],num[v]);
    }
  }
  on_stk[u]=false;
}

void init(){
  memset(num,0,sizeof(num));
  memset(low,0,sizeof(low));
  memset(parent,0,sizeof(parent));
  memset(lab,-1,sizeof(lab));
  memset(deg,0,sizeof(deg));
  memset(on_stk,0,sizeof(on_stk));
  n_lab=0;
  e.clear();
  for(int u=0;u<n;u++)
    G[u].clear(),p[u]=u;
}

int root_of(int u){
  return p[u]=(u==p[u]?u:root_of(p[u]));
}

void join(int u,int v){
  p[root_of(u)]=root_of(v);
}

int main(){
  int T,no=0;
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
    
    dfs(0);
    sort(e.begin(),e.end());

    for(int u=0;u<n;u++)
      for(int i=0;i<(int)G[u].size();i++){
        int v=G[u][i];
        ii edge(min(u,v),max(u,v));
        if(find(e.begin(),e.end(),edge)==e.end())
          join(u,v);
      }

    n_lab=0;
    for(int i=0;i<(int)e.size();i++){
      int r=root_of(e[i].first),s=root_of(e[i].second);
      if(lab[r]==-1)lab[r]=n_lab++;
      if(lab[s]==-1)lab[s]=n_lab++;
      r=lab[r],s=lab[s];
      deg[r]++,deg[s]++;
    }

    int ans=0;
    for(int u=0;u<n_lab;u++)
      if(deg[u]==1)
        ++ans;

    printf("Case %d: ",++no);
    if(ans==0)
      puts("0");
    else
      printf("%d\n",ans/2+(ans&1));
  }
  return 0;
}
