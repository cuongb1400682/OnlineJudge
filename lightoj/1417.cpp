#include<stdio.h>
#include<string.h>
#include<stack>
#include<vector>
using namespace std;

#define N 50005

int num[N],low[N],n_lab,sz[N],n;
bool vis[N],on_cycle[N];
stack<int> stk;
vector<int> G[N];

void tarjan(int u){
  num[u]=low[u]=++n_lab;
  stk.push(u);vis[u]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(num[v]==0){
      tarjan(v);
      low[u]=min(low[u],low[v]);
    }else if(vis[v]){
      low[u]=min(low[u],num[v]);
    }
  }

  if(low[u]==num[u]){
    vector<int> C;
    while(stk.top()!=u){
      vis[stk.top()]=false;
      C.push_back(stk.top());
      stk.pop();
    }
    vis[u]=false;
    C.push_back(u);
    stk.pop();

    for(int i=0;i<(int)C.size();i++){
      sz[C[i]]=(int)C.size();
      on_cycle[C[i]]=(C.size()>=2);
    }
  }
}

void init(){
  n_lab=0;
  for(int u=1;u<=n;u++){
    G[u].clear();
    num[u]=low[u]=0;
    sz[u]=0;
    vis[u]=on_cycle[u]=false;
  }
}

void dfs(int u){
  if(vis[u]||on_cycle[u])return;
  vis[u]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    dfs(v);
    sz[u]=sz[v]+1;
  }  
}

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d",&n);

    init();
    
    for(int i=1;i<=n;i++){
      int u,v;
      scanf("%d%d",&u,&v);
      G[u].push_back(v);
    }

    for(int u=1;u<=n;u++)
      if(num[u]==0)
        tarjan(u);

    memset(vis,0,sizeof(vis));
    for(int u=1;u<=n;u++){
      dfs(u);
    }
    
    int v=1,ans=sz[1];
    for(int u=1;u<=n;u++)
      if(ans<sz[u]||(ans==sz[u]&&v>u))
        ans=sz[u],v=u;

    printf("Case %d: %d\n",++no,v);
  }
  return 0;
}
