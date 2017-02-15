#include <stdio.h>
#include <set>

using namespace std;

#define SZ 100005
#define INF 1000000000000000000LL

typedef long long ll;
typedef pair<ll,ll> ii;

ll n,m,k;
set<ii> G[SZ],T[SZ];

void init(){
  ll u,v,w;
  scanf("%lld%lld%lld",&n,&m,&k);
  for(ll i=1;i<=m;i++){
    scanf("%lld%lld%lld",&u,&v,&w);
    G[u].insert(ii(w,v));
    G[v].insert(ii(w,u));
  }
  for(ll i=1;i<=k;i++){
    scanf("%lld%lld",&u,&w);
    G[1].insert(ii(-w,u));
    G[u].insert(ii(-w,1));
  }
}

void solve(){
  set<ii> q;
  static ll d[SZ];

  for(ll u=1;u<=n;u++)
    d[u]=INF;

  d[1]=0;
  q.insert(ii(0,1));

  while(!q.empty()){
    ll u=q.begin()->second;
    q.erase(q.begin());

    for(set<ii>::iterator it=G[u].begin();it!=G[u].end();it++){
      ll v=it->second;
      ll w=it->first;
      if(w<0) w*=-1;
      if(d[v]>d[u]+w){
        if(d[v]!=INF)
          q.erase(q.find(ii(d[v],v)));
        d[v]=d[u]+w;
        T[v].clear();
        T[v].insert(*it);
        q.insert(ii(d[v],v));
      }else if(d[v]==d[u]+w){
        T[v].insert(*it);
      }
    }
  }

  ll ans=0;
  for(ll u=1;u<=n;u++)
    for(set<ii>::iterator it=T[u].begin();it!=T[u].end();it++){
      ll v=it->second;
      ll w=it->first;
      if(T[u].size()==1&&w<0)
        ++ans;
    }
  printf("%lld\n",k-ans);
}

int main(){
  init();
  solve();
  return 0;
}
