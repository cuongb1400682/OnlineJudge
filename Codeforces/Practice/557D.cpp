#include <stdio.h>
#include <set>
#include <string.h>

using namespace std;

#define SZ 100005

typedef long long ll;

set<ll> G[SZ];
ll n,m,deg[SZ],zero,one,color[SZ];

bool dfs(ll u,ll *color){
  set<ll>::iterator it;
  for(it=G[u].begin();it!=G[u].end();it++){
    if(color[*it]==0){
      color[*it]=(color[u]==1?-1:1);
      if(dfs(*it,color))
        return true;
    }else if(color[u]==color[*it]){
      return true;
    }
  }
  return false;
}

bool has_odd_circle(){
  memset(color,0,sizeof(color));
  for(ll u=1;u<=n;u++)
    if(color[u]==0){
      color[u]=1;
      if(dfs(u,color))
        return true;
    }
  return false;
}

void dfs2(ll u,bool *vis,ll &A,ll &B){
  if(vis[u])
    return;
  vis[u]=true;
  if(color[u]==-1)A++;
  if(color[u]==1)B++;
  set<ll>::iterator it;
  for(it=G[u].begin();it!=G[u].end();it++)
    dfs2(*it,vis,A,B);
}

int main(){
  scanf("%lld%lld",&n,&m);
  for(ll i=1;i<=m;i++){
    ll u,v;
    scanf("%lld%lld",&u,&v);
    G[u].insert(v);
    G[v].insert(u);
    deg[u]++;
    deg[v]++;
  }
  ll t,w;
  if(has_odd_circle()){
    t=0,w=1;
  }else{
    for(ll u=1;u<=n;u++){
      if(deg[u]==0)
        zero++;
      if(deg[u]==1)
        one++;
    }
    if(zero+one==n){
      if(one==n){
        t=2;
        w=(n/2)*(n-2);
      }else if(zero==n){
        t=3;
        w=(n*(n-1)*(n-2))/6;
      }else{
        t=2;
        w=(one/2)*(one-2)+(one/2)*zero;
      }
    }else{
      bool vis[SZ]={false};
      t=1;
      for(ll u=1;u<=n;u++){
        if(!vis[u]){
          ll A=0,B=0;          
          dfs2(u,vis,A,B);
          w+=(A*(A-1))/2+(B*(B-1))/2;
        }
      }
    }
  }
  printf("%lld %lld\n",t,w);
  return 0;
}
