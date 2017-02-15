#include <stdio.h>
#include <set>

using namespace std;

#define SZ 100005
#define INF 1000000000

typedef pair<int,int> ii;

int n,m,d[SZ],n_affected[SZ];
ii parent[SZ];
set<ii> G[SZ];

void dijkstra(){
  set<ii> q;
  
  for(int u=1;u<=n;u++){
    parent[u]=ii(-1,-1);
    d[u]=INF;
    n_affected[u]=0;
  }

  d[1]=0;
  parent[1]=ii(1,0);
  q.insert(ii(0,1));

  while(!q.empty()){
    int u=q.begin()->second;
    q.erase(q.begin());
    for(set<ii>::iterator it=G[u].begin();it!=G[u].end();it++){
      int v=it->first;
      int w=it->second;
      if(d[v]>d[u]+1){
        if(d[v]!=INF)
          q.erase(q.find(ii(d[v],v)));
        d[v]=d[u]+1;
        parent[v]=ii(u,1-w);
        n_affected[v]=n_affected[u]+w;
        q.insert(ii(d[v],v));
      }else if(d[v]==d[u]+1){
        if(n_affected[u]+w<n_affected[v]){
          n_affected[v]=n_affected[u]+w;
          parent[v]=ii(u,1-w);
        }
      }
    }
  }
}

int main(){
  set<ii> blow_up,fixed;
  set<ii>::iterator it;
  
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++){
    int u,v,w;
    scanf("%d%d%d",&u,&v,&w);
    if(u>v) swap(u,v);
    G[u].insert(ii(v,1-w));
    G[v].insert(ii(u,1-w));
    if(w==1)
      blow_up.insert(ii(u,v));
  }
  dijkstra();
  for(int i=n;i!=1;i=parent[i].first){
    int u=i,v=parent[i].first,w=parent[i].second;
    if(u>v) swap(u,v);
    if(w==0){
      fixed.insert(ii(u,v));
    }else{
      blow_up.erase(ii(u,v));      
    }     
  }

  printf("%d\n",int(blow_up.size()+fixed.size()));
  for(it=blow_up.begin();it!=blow_up.end();it++)
    printf("%d %d 0\n",it->first,it->second);
  for(it=fixed.begin();it!=fixed.end();it++)
    printf("%d %d 1\n",it->first,it->second);
  
  return 0;
}
