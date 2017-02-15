#include <stdio.h>
#include <set>

using namespace std;

typedef long long ll;

typedef pair<ll,ll> ii;

#define SZ 200005
#define INF 1000000000

set<ll> G[SZ];
ll a[SZ],n;

ii dfs(ll u){
  set<ll>::iterator it;
  ii ans;
  for(it=G[u].begin();it!=G[u].end();it++){
    ll v=*it;
    ll f=ans.first,s=ans.second;
    ii tmp=dfs(v);
    if(it==G[u].begin())
      ans=tmp;
    else{
      ans.first=max(f+tmp.first,s+tmp.second);
      ans.second=max(f+tmp.second,s+tmp.first);
    }
  }
  ll f=ans.first;
  ans.second=max(ans.second,f+a[u]);
  return ans;
}

int main(){
  scanf("%lld",&n);
  for(ll i=1,p;i<=n;i++){
    scanf("%lld%lld",&p,&a[i]);
    if(p!=-1)
      G[p].insert(i);
  }
  ii tmp=dfs(1);
  printf("%lld\n",max(tmp.first,tmp.second));
  return 0;
}
