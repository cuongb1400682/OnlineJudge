#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;

#define N 105

int n,m,p[N],a[N],b[N];
vector<int> G[N];
bool vis[N];

int dfs(int u){
  if(vis[u])return 0;
  vis[u]=true;
  for(int i=0;i<(int)G[u].size();i++){
    if(p[G[u][i]]==-1||dfs(p[G[u][i]])){
      p[G[u][i]]=u;
      return 1;
    }
  }
  return 0;
}

int solve(){
  int ans=0;
  memset(p,-1,sizeof(p));
  for(int u=1;u<=m;u++){
    memset(vis,0,sizeof(vis));
    ans+=dfs(u);
  }
  return ans;
}

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d",&b[i]);
    for(int i=1;i<=m;i++){
      G[i].clear();
      for(int j=1;j<=n;j++)
        if(b[i]%a[j]==0)
          G[i].push_back(j);
    }
    printf("Case %d: %d\n",++no,solve());
  }
  return 0;
}
