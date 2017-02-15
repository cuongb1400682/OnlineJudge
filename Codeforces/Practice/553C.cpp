#include<stdio.h>
#include<vector>

using namespace std;

#define N 100005
#define M 1000000007

typedef pair<int,int> ii;

int p[N],n,m,color[N],lab[N],n_lab;
vector<ii> e;
vector<int> G[N];

bool has_odd_circle(int u){
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(color[v]==0){
      color[v]=-color[u];
      if(has_odd_circle(v))
        return true;
    }else if(color[v]==color[u]){
      return true;
    }
  }
  return false;
}

int root_of(int u){
  return p[u]=(u==p[u]?u:root_of(p[u]));
}

void join(int u,int v){
  int s=root_of(u),r=root_of(v);
  if(r!=s)p[s]=r,n--;
}

int main(){
  scanf("%d%d",&n,&m);
  for(int u=1;u<=n;u++)
    p[u]=u;
  for(int i=1;i<=m;i++){
    int u,v,w;
    scanf("%d%d%d",&u,&v,&w);
    if(w==1)
      join(u,v);
    else
      e.push_back(ii(u,v));
  }

  for(int i=0;i<(int)e.size();i++){
    int u=root_of(e[i].first),v=root_of(e[i].second);
    if(lab[u]==0)lab[u]=++n_lab;
    if(lab[v]==0)lab[v]=++n_lab;
    u=lab[u],v=lab[v];
    G[u].push_back(v);
    G[v].push_back(u);
  }
  
  int n_comp=0;
  for(int u=1;u<=n;u++){
    if(color[u]!=0)continue;
    color[u]=1;
    if(has_odd_circle(u)){
      puts("0");
      return 0;
    }
    n_comp++;
  }
  long long ans=1;
  for(n_comp--;n_comp>0;n_comp--){
    ans=(ans*2)%M;
  }
  printf("%lld\n",ans);
  return 0;
}
