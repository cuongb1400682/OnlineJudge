#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

#define N 10005
#define INF 0x3f3f3f3f

typedef pair<int,int> ii;

int low[N],num[N],n_lab,T,n,no,parent[N];
bool on_stk[N],vis[N];
vector<int> G[N];
vector<ii> ans;

void dfs(int u){
  low[u]=num[u]=++n_lab;
  on_stk[u]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(num[v]==INF){
      parent[v]=u;
      dfs(v);
      if(low[v]>num[u])
        ans.push_back(u>v?ii(v,u):ii(u,v));
      low[u]=min(low[u],low[v]);
    }else if(on_stk[v]&&parent[u]!=v){
      low[u]=min(low[u],num[v]);
    }
  }
  on_stk[u]=false;
}

int main(){
  scanf("%d",&T);
  while(T--){
    scanf("%d",&n);

    for(int u=0;u<N;u++)
      G[u].clear();
    ans.clear();
    n_lab=0;
    memset(low,0x3f,sizeof(low));
    memset(num,0x3f,sizeof(num));
    memset(on_stk,0,sizeof(on_stk));
    memset(vis,0,sizeof(vis));
    
    for(int i=1;i<=n;i++){
      int u,v,deg;
      scanf("%d (%d)",&u,&deg);
      while(deg--){
        scanf("%d",&v);
        G[u].push_back(v);
      }
    }

    for(int u=0;u<n;u++)
      if(num[u]==INF)
        dfs(u);
    printf("Case %d:\n",++no);
    printf("%d critical links\n",(int)ans.size());
    sort(ans.begin(),ans.end());
    for(int i=0;i<(int)ans.size();i++)
      printf("%d - %d\n",ans[i].first,ans[i].second);
  }
  return 0;
}
