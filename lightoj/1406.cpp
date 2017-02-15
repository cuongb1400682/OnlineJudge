#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

#define N 16
#define INF 1000000000

int n,m,dp[1<<N];
bool is_path[1<<N],vis[N][1<<N];
vector<int> G[N];

void dfs(int u,int st){
  if(vis[u][st])return;
  vis[u][st]=true;
  is_path[st]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    dfs(v,st|(1<<v));
  }
}

int solve(int st){
  if(dp[st]!=-1)
    return dp[st];
  int ans=INF;
  for(int i=st;i;i=st&(i-1)){
    if(is_path[i])
      ans=min(ans,solve(st-i)+1);
  }
  return dp[st]=ans;
}

int main(){
  int ntest,no=0;
  scanf("%d",&ntest);
  while(ntest--){
    scanf("%d%d",&n,&m);
    for(int u=0;u<n;u++)G[u].clear();
    for(int i=1,u,v;i<=m;i++){
      scanf("%d%d",&u,&v);
      u--,v--;
      G[u].push_back(v);
    }
    memset(dp,-1,sizeof(dp));
    memset(is_path,false,sizeof(is_path));
    memset(vis,false,sizeof(vis));
    dp[0]=0;
    for(int u=0;u<n;u++)
      dfs(u,1<<u);
    printf("Case %d: %d\n",++no,solve((1<<n)-1));
  }
  return 0;
}

