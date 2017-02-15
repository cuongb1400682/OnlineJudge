#include <stdio.h>
#include <string.h>
#include <set>
#include <vector>
using namespace std;

#define SZ 256

typedef pair<int,int> ii;

int dist[SZ],n;
set<int> G[SZ];
vector<ii> e;

ii dfs(int u){
  ii ans(dist[u],u);
  for(set<int>::iterator it=G[u].begin();it!=G[u].end();it++){
    int v=*it;
    if(dist[v]==0){
      dist[v]=dist[u]+1;
      ii tmp=dfs(v);
      if(ans.first<tmp.first)
        ans=tmp;
    }
  }
  return ans;
}

int diameter(int u){
  memset(dist,0,sizeof(dist));
  dist[u]=1;
  int v=dfs(u).second;
  memset(dist,0,sizeof(dist));
  dist[v]=1;
  return dfs(v).first;
}

int main(){
  scanf("%d",&n);
  for(int i=1;i<=n-1;i++){
    int u,v;
    scanf("%d%d",&u,&v);
    G[u].insert(v);
    G[v].insert(u);
    e.push_back(ii(u,v));
  }
  
  int ans=-1;
  
  for(int i=0;i<(int)e.size();i++){
    int u=e[i].first,v=e[i].second;
    G[u].erase(v);
    G[v].erase(u);
    int d1=diameter(u)-1;
    int d2=diameter(v)-1;
    if(d1*d2>ans)
      ans=d1*d2;
    G[u].insert(v);
    G[v].insert(u);        
  }
  printf("%d\n",ans);
  return 0;
}
