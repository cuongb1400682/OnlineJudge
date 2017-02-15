#include <stdio.h>
#include <string.h>
#include <set>

using namespace std;

typedef long long ll;

#define SZ 200005

struct Res{
  int n,sum,mind;
  Res(int mind=0,int n=0,int sum=0):
    mind(mind),n(n),sum(sum){}
};

set<int> G[SZ];
int n,k,c[SZ];
ll ans;
bool univ[SZ];

void dfs(int u,int p){
  if(univ[u])
    c[u]++;
  for(set<int>::iterator i=G[u].begin();i!=G[u].end();i++){
    int v=*i;
    if(v==p) continue;
    dfs(v,u);
    ans+=min<ll>(c[v],2*k-c[v]);
    c[u]+=c[v];
  }  
}

int main(){
  scanf("%d%d",&n,&k);
  memset(univ,0,sizeof(univ));
  for(int i=1,u;i<=2*k;i++){
    scanf("%d",&u);
    univ[u]=true;
  }
  for(int i=1,u,v;i<=n-1;i++){
    scanf("%d%d",&u,&v);
    G[u].insert(v);
    G[v].insert(u);
  }
  dfs(1,1);
  printf("%I64d\n",ans);
  return 0;
}

