#include <stdio.h>
#include <set>

using namespace std;

#define SZ 100005

typedef long long ll;
typedef pair<ll,ll> ii;

set<ii> G[SZ];
ll n;

ii dfs(ll u,ll p){
  if(G[u].size()==1&&u!=1)
    return ii(0,0);  
  set<ii>::iterator it;
  ll total=0,comp=0;
  for(it=G[u].begin();it!=G[u].end();it++){
    ll v=it->first;
    ll w=it->second;
    if(v!=p){
      ii tmp=dfs(v,u);
      tmp.first+=2*w;
      tmp.second+=w;
      total+=tmp.first;
      comp=min(comp,(tmp.second-tmp.first));
    }
  }
  return ii(total,total+comp);
}

int main(){
  scanf("%lld",&n);
  for(ll i=1;i<=n-1;i++){
    ll u,v,w;
    scanf("%lld%lld%lld",&u,&v,&w);
    G[u].insert(ii(v,w));
    G[v].insert(ii(u,w));
  }
  printf("%lld\n",dfs(1,1).second);
  return 0;
}
