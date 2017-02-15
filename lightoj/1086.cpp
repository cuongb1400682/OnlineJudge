#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;

#define N 16
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long ll;
typedef pair<ll,ll> ii;

ll dp[1<<N],n,m,a[N][N],deg[N],target;

ll solve(ll st){
  if(dp[st]!=-1)
    return dp[st];
  ll ans=INF;
  for(ll u=0;u<n-1;u++){
    if(!(deg[u]&1)||!((st>>u)&1))continue;
    for(ll v=u+1;v<n;v++){
      if(!(deg[v]&1)||a[u][v]>=INF||!((st>>v)&1))continue;
      ans=min(ans,solve(st-(1<<u)-(1<<v))+a[u][v]);
    }    
  }
  return dp[st]=ans;
}

int main(){
  ll nTest,no=0;
  scanf("%lld",&nTest);
  while(nTest--){
    scanf("%lld%lld",&n,&m);
    memset(a,0x3f,sizeof(a));
    memset(deg,0,sizeof(deg));
    ll ans=0;
    for(ll i=0;i<m;i++){
      ll u,v,w;
      scanf("%lld%lld%lld",&u,&v,&w);
      u--,v--;
      a[u][v]=min(a[u][v],w);
      a[v][u]=min(a[v][u],w);
      deg[u]++;
      deg[v]++;
      ans+=w;
    }
    target=(1<<n)-1;
    for(ll u=0;u<n;u++){
      a[u][u]=0;
      if(deg[u]&1)
        target-=(1<<u);
    }
    for(ll k=0;k<n;k++)
      for(ll u=0;u<n;u++){
        if(a[u][k]>=INF)continue;
        for(ll v=0;v<n;v++){
          if(a[k][v]>=INF)continue;
          if(a[u][v]>a[u][k]+a[k][v])
            a[u][v]=a[u][k]+a[k][v];
        }
      }
    memset(dp,-1,sizeof(dp));
    dp[target]=0;
    ans+=solve((1<<n)-1);
    printf("Case %lld: %lld\n",++no,ans);
  }
  return 0;
}
