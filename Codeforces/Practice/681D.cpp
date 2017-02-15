#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

#define N 100005

vector<int> G[N],C,ans;
int depth[N],n,m,p[N];
bool has_ancestor[N],vis[N];

bool dfs(int u,int max_depth){
  if(!vis[p[u]])C.push_back(p[u]);
  vis[p[u]]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    depth[v]=depth[u]+1;
    if(max_depth>depth[p[v]]||dfs(v,max(max_depth,depth[p[v]])))
      return true;
  }
  return false;
}

bool cmp(int x,int y){
  return depth[x]>depth[y];
}

int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++){
    int u,v;
    scanf("%d%d",&u,&v);
    G[u].push_back(v);
    has_ancestor[v]=true;
  }
  for(int i=1;i<=n;i++)
    scanf("%d",&p[i]);
  for(int u=1;u<=n;u++)
    if(!has_ancestor[u]){
      C.clear();
      memset(vis,0,sizeof(vis));
      depth[u]=1;
      if(dfs(u,1)){
        puts("-1");
        return 0;
      }else{
        sort(C.begin(),C.end(),cmp);
        for(int i=0;i<(int)C.size();i++){
          if(C[i]!=p[C[i]]){
            puts("-1");
            return 0;
          }
          ans.push_back(C[i]);
        }
      }
    }
  printf("%d\n",(int)ans.size());
  for(int i=0;i<(int)ans.size();i++)
    printf("%d\n",ans[i]);
  return 0;
}
