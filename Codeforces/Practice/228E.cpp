#include <stdio.h>
#include <string.h>
#include <stack>
#include <vector>
#include <set>

using namespace std;

#define SZ 256

int num[SZ],low[SZ],comp[SZ],n_lab,n,m,n_comp,val[SZ];
bool on_stk[SZ],vis[SZ];
stack<int> stk;
vector<int> G[SZ];

void tarjan(int u){
  num[u]=low[u]=++n_lab;
  stk.push(u);on_stk[u]=true;
  vis[u]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(num[v]==0){
      tarjan(v);
      low[u]=min(low[u],low[v]);
    }else if(on_stk[v]){
      low[u]=min(low[u],num[v]);
    }
  }
  if(num[u]==low[u]){
    ++n_comp;
    while(stk.top()!=u){
      on_stk[stk.top()]=false;
      comp[stk.top()]=n_comp;
      stk.pop();
    }
    comp[u]=n_comp;
    stk.pop();
    on_stk[u]=false;
  }
}

int main(){
  scanf("%d%d",&n,&m);
  for(int i=1,u,v,w;i<=m;i++){
    scanf("%d%d%d",&u,&v,&w);
    u<<=1,v<<=1;
    if(w==0){
      G[u^1].push_back(v);
      G[v^1].push_back(u);
      G[v].push_back(u^1);
      G[u].push_back(v^1);
    }else{
      G[u].push_back(v);
      G[v].push_back(u);
      G[u^1].push_back(v^1);
      G[v^1].push_back(u^1);
    }      
  }

  for(int u=2;u<=2*n+1;u++){
    if(!vis[u]){
      tarjan(u);
    }
  }

  for(int u=1;u<=n;u++){
    if(comp[2*u]==comp[2*u+1]){
      puts("Impossible");
      return 0;
    }
  }

  set<int> ans;
  memset(val,-1,sizeof(val));
  for(int u=2;u<=2*n+1;u++){
    if(val[comp[u]]==-1){
      val[comp[u]]=1;
      ans.insert(u/2);
      val[comp[u^1]]=0;
    }
    if(val[comp[u]]==1&&!(u&1))
      ans.insert(u/2);
  }

  printf("%d\n",(int)ans.size());
  for(set<int>::iterator it=ans.begin();it!=ans.end();it++)
    printf("%d ",*it);
  printf("\n");
  
  return 0;
}
