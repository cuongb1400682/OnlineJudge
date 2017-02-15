#include <iostream>
#include <algorithm>

using namespace std;

#define SZ 100005

typedef long long ll;
typedef pair<ll,ll> ii;

ll n,m;
ii a[SZ];

ll H(ll n){
  if(n<=2)
    return n;
  if(n&1)
    return (n*(n-1))/2+1;
  else
    return n*n/2;
}

ll lb(ll n){
  ll i,j;
  for(i=1,j=m+1;i<j;){
    ll mid=(i+j)>>1;
    if(H(mid)>n)
      j=mid;
    else
      i=mid+1;
  }
  return i;
}

int main(){
  cin>>n>>m;
  for(ll i=1;i<=m;i++)
    cin>>a[i].second>>a[i].first;
  sort(a+1,a+1+m);
  reverse(a+1,a+1+m);
  
  ll x;
  if(n<3)
    x=min(n,m);
  else
    x=min(lb(n)-1,m);

  ll ans=0;
  for(ll i=1;i<=x;i++)
    ans+=a[i].first;
  cout<<ans<<'\n';
  return 0;
}
