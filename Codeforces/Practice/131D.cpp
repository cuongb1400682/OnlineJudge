#include <stdio.h>
#include <string.h>
#include <set>

using namespace std;

#define SZ 3005

int parent[SZ],n,dist[SZ];
bool in_circle[SZ],vis[SZ];
set<int> G[SZ];

bool find_the_ring(int u,int &s,int &t){
  for(set<int>::iterator it=G[u].begin();it!=G[u].end();it++){
    int v=*it;
    if(parent[v]==0){
      parent[v]=u;
      if(find_the_ring(v,s,t))
        return true;
    }else if(v!=parent[u]&&u!=parent[v]){
      s=u;
      t=v;
      return true;
    }
  }
  return false;
}

void mark(int s,int t){
  int x=0;
  for(int u=s;u!=-1;u=parent[u])
    in_circle[u]=true;
  for(int u=t;t!=-1;t=parent[t]) {
    if(in_circle[u]){
      x=u;
      break;
    }
    in_circle[u]=true;
  }
  while(x!=0){
    x=parent[x];
    in_circle[x]=false;
  }
}

void dfs(int u,bool *vis){
  for(set<int>::iterator it=G[u].begin();it!=G[u].end();it++){
    int v=*it;
    if(!vis[v]){
      vis[v]=true;
      dist[v]=dist[u]+1;
      dfs(v,vis);
    }
  }
}

int main(){
  scanf("%d", &n);
  for(int i=1;i<=n;i++){
    int u,v;
    scanf("%d%d",&u,&v);
    G[u].insert(v);
    G[v].insert(u);
  }

  int s,t;
  memset(parent,0,sizeof(parent));
  parent[1]=-1;
  find_the_ring(1,s,t);

  memset(in_circle,false,sizeof(in_circle));
  mark(s,t);

  memset(dist,0,sizeof(dist));
  memcpy(vis,in_circle,sizeof(vis));
  for(int u=1;u<=n;u++)
    if(in_circle[u]){
      vis[u]=true;
      dfs(u,vis);
    }

  for(int u=1;u<=n;u++)
    printf("%d ",dist[u]);
  printf("\n");
  
  return 0;
}
