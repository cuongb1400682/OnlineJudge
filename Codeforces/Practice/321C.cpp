#include <stdio.h>
#include <vector>

using namespace std;

#define N 100005

int sz[N],level[N],n;
vector<int> G[N];
bool vis[N];

int calc_sz(int u,int p){
  sz[u]=1;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(v==p||vis[v])continue;
    sz[u]+=calc_sz(v,u);
  }
  return sz[u];
}

int get_center(int u,int p,int n){
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(v==p||vis[v])continue;
    if(sz[v]>=n/2)
      return get_center(v,u,n);
  }
  return u;
}

int decompose(int u,int lv){
  calc_sz(u,u);
  int cen=get_center(u,u,sz[u]);
  vis[cen]=true;
  level[cen]=lv; 
  for(int i=0;i<(int)G[cen].size();i++)
    if(!vis[G[cen][i]])decompose(G[cen][i],lv+1);
  return cen;
}

int main(){
  scanf("%d",&n);
  for(int i=1;i<=n-1;i++){
    int u,v;
    scanf("%d%d",&u,&v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  decompose(1,0);
  for(int u=1;u<=n;u++)
    printf("%c ",level[u]+'A');
  printf("\n");
  return 0;
}
