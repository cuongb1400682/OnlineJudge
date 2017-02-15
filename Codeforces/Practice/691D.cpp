#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define SZ 1000005

int n,m,a[SZ],P[SZ],nP;
vector<int> G[SZ];
bool vis[SZ];

void bfs(int u){
  queue<int> q;
  q.push(u);vis[u]=true;
  while(!q.empty()){
    u=q.front();q.pop();
    P[nP++]=u;
    for(int i=0;i<(int)G[u].size();i++){
      if(!vis[G[u][i]]){
        vis[G[u][i]]=true;
        q.push(G[u][i]);
      }
    }
  }
}

void quick_sort(int l,int r){
  if(l>=r) return;
  int pivot=a[P[(l+r)>>1]];
  int i=l,j=r;
  while(i<=j){
    while(a[P[i]]>pivot) i++;
    while(a[P[j]]<pivot) j--;
    if(i<=j){
      swap(a[P[i]],a[P[j]]);
      i++,j--;
    }
  }
  quick_sort(l,j);
  quick_sort(i,r);
}

int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
  for(int i=1;i<=m;i++){
    int u,v;
    scanf("%d%d",&u,&v);
    if(u==v) continue;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  for(int u=1;u<=n;u++)
    G[u].resize(unique(G[u].begin(),G[u].end())-G[u].begin());
  
  for(int u=1;u<=n;u++)
    if(!vis[u]){
      nP=0;
      bfs(u);
      sort(P,P+nP);
      quick_sort(0,nP-1);
    }
  for(int i=1;i<=n;i++)
    printf("%d ",a[i]);
  printf("\n");
  return 0;
}
