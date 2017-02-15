#include <stdio.h>
#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

#define SZ 105

typedef long long ll;

ll n,m,d1[SZ],dn[SZ],c1[SZ],cn[SZ];
vector<ll> G[SZ];

void bfs(ll s,ll *d,ll *cnt){
  queue<ll> q;
  bool vis[SZ]={false};
  for(ll u=1;u<=n;u++){
    d[u]=0;
    cnt[u]=1;
    vis[u]=false;
  }
  q.push(s);
  vis[s]=true;
  while(!q.empty()){
    ll u=q.front();
    q.pop();
    for(ll i=0;i<(ll)G[u].size();i++){
      ll v=G[u][i];
      if(!vis[v]){
        vis[v]=true;
        cnt[v]=cnt[u];
        d[v]=d[u]+1;
        q.push(v);
      }else{
        if(d[v]==d[u]+1){
          cnt[v]+=cnt[u];
        }else if(d[v]>d[u]+1){
          d[v]=d[u]+1;
          cnt[v]=cnt[v];
        }
      }
    }
  }
}

int main(){
  cin>>n>>m;
  for(ll i=1;i<=m;i++){
    ll u,v;
    cin>>u>>v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  bfs(1,d1,c1);
  bfs(n,dn,cn);
  long double ans=1.0,tmp;
  for(ll v=2;v<=n-1;v++){
    if(d1[v]+dn[v]==d1[n]){
      tmp=(long double)(2.0*c1[v]*cn[v])/c1[n];
      if(ans<tmp)
        ans=tmp;
    }
  }
  cout<<setprecision(12)<<fixed<<ans<<'\n';
  return 0;
}
