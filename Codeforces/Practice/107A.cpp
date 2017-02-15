#include <stdio.h>
#include <set>
#include <vector>

using namespace std;

typedef pair<int,int> ii;

#define SZ 1024
#define INF 1000000000

set<ii> G[SZ];
bool vis[SZ];
int n,p,deg_in[SZ];

ii dfs(int u){
  ii ans(INF,INF);
  for(set<ii>::iterator it=G[u].begin();it!=G[u].end();it++){
    int v=it->second,w=it->first;
    if(!vis[v]){
      vis[v]=true;
      ii tmp=dfs(v);
      ans.first=tmp.first;
      ans.second=min(w,tmp.second);
    }
  }
  if(G[u].size()==0)
    ans.first=u;
  return ans;
}

int main(){
  scanf("%d%d",&n,&p);
  for(int i=1;i<=p;i++){
    int u,v,w;
    scanf("%d%d%d",&u,&v,&w);
    G[u].insert(ii(w,v));
    deg_in[v]++;
  }

  vector<pair<int,ii> > ans;
  for(int u=1;u<=n;u++){
    if(deg_in[u]==0&&!vis[u]){
      vis[u]=true;
      ii t=dfs(u);
      if(t.second!=INF)
        ans.push_back(make_pair(u, t));
    }
  }

  printf("%d\n", (int) ans.size());
  for(int i=0;i<(int)ans.size();i++)
    printf("%d %d %d\n",ans[i].first,ans[i].second.first,ans[i].second.second);
  
  return 0;
}
