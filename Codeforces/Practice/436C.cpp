#include <stdio.h>
#include <string.h>
#include <set>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

#define SZ 1024
#define INF 1000000000

char level[SZ][16][16];
int n,m,k,w,a[SZ][SZ],d[SZ],parent[SZ];
set<int> G[SZ];

int diff(char (*a)[16], char (*b)[16]){
  int ans=0;
  for(int i=1;i<=n;i++)
    for(int j=0;j<m;j++)
      ans+=(a[i][j]!=b[i][j]);
  return ans;
}

void init() {
  scanf("%d%d%d%d",&n,&m,&k,&w);
  for(int l=1;l<=k;l++){
    for(int i=1;i<=n;i++)
      scanf(" %s ",level[l][i]);
  }

  for(int i=1;i<=k;i++){
    for(int j=1;j<=k;j++)
      a[i][j]=w*diff(level[i],level[j]);
    a[i][0]=n*m;
    a[0][i]=n*m;
  }
}

void solve(){
  set<ii> q;
  bool vis[SZ]={false};
  for(int u=0;u<=k;u++){
    d[u]=INF;
    parent[u]=-1;
  }

  d[0]=0;
  parent[0]=0;
  q.insert(ii(0,0));

  while(!q.empty()){
    int u=q.begin()->second;
    q.erase(q.begin());
    vis[u]=true;
    for(int v=0;v<=k;v++){
      if(u!=v && !vis[v]){
        if(d[v]>a[u][v]){
          if(d[v]!=INF)
            q.erase(q.find(ii(d[v],v)));
          d[v]=a[u][v];
          parent[v]=u;
          q.insert(ii(d[v],v));
        }
      }
    }
  }
}

void dfs(int u,bool *vis,vector<int> &z){
  for(set<int>::iterator v=G[u].begin();v!=G[u].end();v++){
    if(!vis[*v]){
      vis[*v]=true;
      dfs(*v,vis,z);
    }
  }
  z.push_back(u);
}

void print(){
  int byte=0;
  for(int u=1;u<=k;u++){
    byte+=a[parent[u]][u];
  }
  printf("%d\n",byte);
  bool vis[SZ]={false};
  for(int u=1;u<=k;u++){
    G[u].insert(parent[u]);
    vis[parent[u]]=true;
  }
  for(int u=1;u<=k;u++)
    if(!vis[u])
      G[k+1].insert(u);
  memset(vis,false,sizeof(vis));
  vector<int> z;
  dfs(k+1,vis,z);
  for(int i=1;i<=(int)z.size()-2;i++)
    printf("%d %d\n",z[i],parent[z[i]]);
}

int main(){
  init();
  solve();
  print();
  return 0;
}
