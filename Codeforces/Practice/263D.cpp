#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <vector>
#include <string.h>

using namespace std;

#define SZ 100005

typedef pair<int,int> ii;

set<int> G[SZ];
bool vis[SZ];
int deg[SZ],parent[SZ],depth[SZ],k,n,m;

void remove_leaf(int u){
  for(set<int>::iterator it=G[u].begin();it!=G[u].end();it++){
    if(!vis[*it]){
      vis[*it]=true;
      remove_leaf(*it);
    }
  }
  if(deg[u]==1){
    int v=*G[u].begin();
    G[u].erase(v);
    G[v].erase(u);
    deg[u]--;
    deg[v]--;
  }
}

ii dfs(int u){
  for(set<int>::iterator it=G[u].begin();it!=G[u].end();it++){
    if(parent[*it]==0){
      parent[*it]=u;
      depth[*it]=depth[u]+1;
      ii tmp=dfs(*it);
      if(tmp!=ii(-1,-1))
        return tmp;
      parent[*it]=0;
      depth[*it]=0;
    }else if(parent[*it]!=u&&parent[u]!=*it){
      int lv=abs(depth[u]-depth[*it])+1;
      if(lv>=k+1){        
        return ii(u,*it);
      }
    }
  }
  return ii(-1,-1);
}

void print(int u,int v){
  vector<int> ans;
  for(;u!=v;u=parent[u])
    ans.push_back(u);
  ans.push_back(v);
  printf("%d\n",(int)ans.size());
  for(int i=0;i<(int)ans.size();i++)
    printf("%d ",ans[i]);
  printf("\n");
}

int main(){
  scanf("%d%d%d",&n,&m,&k);
  for(int i=1;i<=m;i++){
    int u,v;
    scanf("%d%d",&u,&v);
    G[u].insert(v);
    G[v].insert(u);
    deg[u]++;
    deg[v]++;
  }

  memset(vis,false,sizeof(vis));
  remove_leaf(1);

  for(int u=1;u<=n;u++)
    if(deg[u]>0){
      depth[u]=1;
      parent[u]=u;
      ii tmp=dfs(u);
      depth[u]=0;
      parent[u]=0;
      if(tmp!=ii(-1,-1))
        print(tmp.first,tmp.second);
      break;
    }
  return 0;
}
