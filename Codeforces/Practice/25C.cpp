#include <stdio.h>
#include <algorithm>

using namespace std;

#define SZ 512

typedef long long ll;

ll a[SZ][SZ],q,n;

int main(){
  ll ans=0,u,v,w;
  scanf("%lld",&n);
  for(ll u=1;u<=n;u++)
    for(ll v=1;v<=n;v++)
      scanf("%lld",&a[u][v]),ans+=a[u][v];

  scanf("%lld",&q);
  while(q--){
    scanf("%lld%lld%lld",&u,&v,&w);
    for(ll i=1;i<=n;i++)
      for(ll j=1;j<=n;j++){
        if(i==j) continue;
        for(ll z=1;z<=2;z++){
          swap(u,v);
          ll tmp=a[i][u]+w+a[v][j];
          if(tmp<a[i][j]){
            ans=ans-(a[i][j]-tmp);
            a[i][j]=tmp;
          }
        }
      }
    printf("%lld\n",ans/2);
  }
  
  printf("\n");
  return 0;
}
