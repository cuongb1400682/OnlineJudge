#include <stdio.h>
#include <stack>
#include <vector>

using namespace std;

#define SZ 2005

int n,num[SZ],low[SZ],n_lab,n_component;
stack<int> stk;
bool on_stk[SZ],vis[SZ];
vector<int> G[SZ];

void dfs(int u){
  num[u]=low[u]=++n_lab;
  stk.push(u);on_stk[u]=true;
  vis[u]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(num[v]==0){
      dfs(v);
      low[u]=min(low[u],low[v]);
    }else if(on_stk[v]){
      low[u]=min(low[u],num[v]);
    }
  }
  if(num[u]==low[u]){
    while(stk.top()!=u){
      on_stk[stk.top()]=false;
      stk.pop();
    }
    on_stk[u]=false;
    stk.pop();
    ++n_component;
  }
}

int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
      int w;
      scanf("%d",&w);
      if(w>0){
        G[i].push_back(j);
      }
    }      


  for(int u=1;u<=n;u++)
    if(!vis[u])
      dfs(u);
  if(n_component==1)
    puts("YES");
  else
    puts("NO");
  
  return 0;
}
