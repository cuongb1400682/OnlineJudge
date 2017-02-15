#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

#define SZ 3005

#define P(a) print_vec(a,#a)

typedef pair<int,int> ii;

int n,m,t1,t2,s1,s2,l1,l2,d[SZ][SZ];
vector<int> G[SZ];

void print_vec(int *a,const char*name){
  printf("%s={",name);
  for(int i=1;i<=n;i++)
    printf("[%d]%d%s",i,a[i],(i==n?"}\n":", "));
}

void sssp(int s, int *d) {
  static bool vis[SZ];
  queue<ii> q;
    
  for(int u=1;u<=n;u++)
    d[u]=0,vis[u]=false;
  d[s]=0;
  q.push(ii(0,s));
  vis[s]=true;
  
  while(!q.empty()){
    int w=q.front().first;
    int u=q.front().second;
    q.pop();
    for(int i=0;i<(int)G[u].size();i++){
      int v=G[u][i];
      if(!vis[v]){
        vis[v]=true;
        d[v]=w+1;
        q.push(ii(d[v],v));
      }
    }
  }
}

void init() {
  scanf("%d%d",&n,&m);
  for(int i=0;i<m;i++){
    int u,v;
    scanf("%d%d",&u,&v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  scanf("%d%d%d",&s1,&t1,&l1);
  scanf("%d%d%d",&s2,&t2,&l2);
}

void solve(){
  for(int u=1;u<=n;u++)
    sssp(u,d[u]);

  if(d[s1][t1]>l1||d[s2][t2]>l2)
    puts("-1");
  else {
    int ans=m-(d[s1][t1]+d[s2][t2]);
    for(int u=1;u<=n;u++){
      for(int v=1;v<=n;v++){
        for (int i=1;i<=2;i++) {
          swap(s1,t1);
          int d1=d[s1][u]+d[u][v]+d[v][t1];
          int d2=d[s2][u]+d[u][v]+d[v][t2];
          if(d1<=l1&&d2<=l2) {
            ans=max(ans,m-(d1+d2-d[u][v]));
          }
        }
      }
    }
    printf("%d\n",ans);
  }
}

int main() {
  init();
  solve();
  return 0;
}
