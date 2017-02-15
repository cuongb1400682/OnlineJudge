#include <stdio.h>
#include <set>
#include <map>

using namespace std;

#define SZ 100005

typedef pair<int,int> ii;

int n,parent[SZ],deg[SZ],s,n_lab;
set<int> G[SZ];
map<int,int> lab,delab;

ii dfs(int u){
  ii ans(1,u);
  for(set<int>::iterator it=G[u].begin();it!=G[u].end();it++){
    if(parent[*it]==0){
      parent[*it]=u;      
      ii tmp=dfs(*it);
      if(ans.first<tmp.first+1)
        ans=tmp,ans.first++;
    }
  }
  return ans;
}

int main(){
  scanf("%d",&n);
  n_lab=0;
  for(int i=1;i<=n;i++){
    int u,v;
    scanf("%d%d",&u,&v);
    if(lab.count(u)==0) lab[u]=++n_lab,delab[lab[u]]=u;
    if(lab.count(v)==0) lab[v]=++n_lab,delab[lab[v]]=v;
    u=lab[u],v=lab[v];
    G[u].insert(v);
    G[v].insert(u);
    deg[u]++;
    deg[v]++;
  }

  s=1;
  for(int u=1;u<=n;u++)
    if(deg[s]>deg[u])
      s=u;

  parent[s]=s;
  ii tmp=dfs(s);

  for(int u=tmp.second;u!=s;u=parent[u])
    printf("%d ",delab[u]);
  printf("%d\n",delab[s]);

  return 0;
}
