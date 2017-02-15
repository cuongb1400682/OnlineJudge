#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>

using namespace std;

#define N 20

typedef long long ll;

ll dp[(1<<N)-1][N],n,m,k,a[N][N],p[N];

ll max(ll a,ll b){return a>b?a:b;}

ll cnt_bit(ll x){
  ll ans=0;
  while(x>0)
    x=x&(x-1),ans++;
  return ans;
}

ll rec(ll i,ll st,ll u){
  if(dp[st][u]!=-1)
    return dp[st][u];
  if(i>=m)
    return 0;
  ll ans=-1;
  for(ll v=1;v<=n;v++)
    if(!((st>>v)&1))
      ans=max(ans,rec(i+1,st|(1<<v),v)+a[u][v]+p[v]);
  return dp[st][u]=ans;
}

int cmp(int x,int y){
  return cnt_bit(x)<cnt_bit(y);
}

ll solve(){
  vector<ll> S;
  for(ll i=1;i<(1<<n);i++)
    if(cnt_bit(i<<1)<=m)
      S.push_back(i<<1);
  sort(S.begin(),S.end(),cmp);
  for(ll u=1;u<=n;u++)
    dp[1<<u][u]=p[u];
  for(ll i=0;i<(ll)S.size();i++){
    ll st=S[i];
    for(ll u=1;u<=n;u++)
      for(ll v=1;v<=n;v++)
        if(((st>>u)&1)&&!((st>>v)&1))
          dp[st|(1<<v)][v]=max(dp[st|(1<<v)][v],dp[st][u]+p[v]+a[u][v]);
  }
  ll ans=0;
  for(ll i=0;i<(ll)S.size();i++){
    if(cnt_bit(S[i])!=m)continue;
    for(ll u=1;u<=n;u++)
      if((S[i]>>u)&1)
        ans=max(ans,dp[S[i]][u]);
  }
  return ans;
}

int main(){
  scanf("%lld%lld%lld",&n,&m,&k);
  for(ll i=1;i<=n;i++)
    scanf("%lld",&p[i]);
  for(ll i=1,u,v,w;i<=k;i++){
    scanf("%lld%lld%lld",&u,&v,&w);
    a[u][v]=w;
  }
  memset(dp,0,sizeof(dp));
  printf("%lld\n",solve());
  return 0;
}

