#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>

using namespace std;

bool a[5005][5005],vis[5005],vv[5005],on_stk[5005];
vector<int> G[5005];
int n,x[3];
int lab[5005],low[5005],n_lable,grp[5005],n_grp;
stack<int> stk;

void tarjan(int u){
  lab[u]=low[u]=++n_lable;
  stk.push(u);on_stk[u]=true;
  vis[u]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(lab[v]==0){
      tarjan(v);
      low[u]=min(low[u],low[v]);
    }else if(on_stk[v]){
      low[u]=min(low[u],lab[v]);
    }
  }
  if(low[u]==lab[u]){
    ++n_grp;
    while(stk.top()!=u){
      grp[stk.top()]=n_grp;
      on_stk[stk.top()]=false;
      stk.pop();
    }
    grp[stk.top()]=n_grp;
    on_stk[stk.top()]=false;
    stk.pop();
  }
}

bool dfs(int u,int depth){
  if(depth==3){
    if(a[x[2]][x[0]])
      return true;
    return false;
  }
  vv[u]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(!vis[v]){
      vis[v]=true;
      x[depth]=v;
      if(dfs(v,depth+1))
        return true;
      vis[v]=false;
    }
  }
  return false;
}

int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++){
    char buf[5005];
    scanf("%s",buf+1);
    for(int j=1;j<=n;j++)
      if(buf[j]=='1'){
        a[i][j]=true;
        G[i].push_back(j);
      }
  }

  memset(vis,false,sizeof(vis));
  for(int u=1;u<=n;u++)
    if(!vis[u])
      tarjan(u);

  memset(vv,false,sizeof(vv));
  for(int u=1;u<=n;u++){
    if(vv[u])
      continue;
    memset(vis,false,sizeof(vis));
    x[0]=u;
    vis[u]=true;
    if(dfs(u,1)){
      printf("%d %d %d\n",x[0],x[1],x[2]);
      return 0;
    }
  }
  puts("-1");
  return 0;
}
