#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include <stdlib.h>

using namespace std;
#define MOD 1000000007LL
#define MAX_N 100005

typedef long long ll;
typedef struct {
  vector<int> lazy;
  ll sum;
} Node;

ll sum[MAX_N];
int n,q;
Node st[4*MAX_N];

void calc_sum() {
  int f,s,t;
  ll product;
  sum[0]=0;
  for (int i = 1; i <= MAX_N; i++) {
    f=i,s=i+1,t=i+2;
    product = (ll)((f*s%MOD)*t%MOD);
    sum[i]=(sum[i-1]+product)%MOD;
  }
}

ll get_sum(int L,int R,int x) {
  int left=abs(L-x)+1;
  int right=abs(R-x)+1;
  ll ans=sum[right]-sum[left-1];
  return ans<0?(ans+MOD):(ans%MOD);
}

void inc(Node *st, int p, int L,int R, int x) {
  st[p].lazy.push_back(x);
  st[p].sum=(st[p].sum+get_sum(L,R,x))%MOD;
}

void dec(Node *st, int p, int L,int R, int x) {
  st[p].lazy.push_back(-x);
  st[p].sum=st[p].sum-get_sum(L,R,x);
  if (st[p].sum < 0){
    st[p].sum+=MOD;
  }
}

void init(Node *st, int p,int L,int R){
  st[p].lazy.clear();
  st[p].sum=0;
  if(L==R){
    return;
  }
  int mid=(L+R)/2;
  init(st,2*p,L,mid);
  init(st,2*p+1,mid+1,R);
}

void propagate(Node *st,int p,int L,int R) {
  if(!st[p].lazy.empty()) {
    int mid=(L+R)/2;
    for (int i=0;i<st[p].lazy.size();i++) {
      int xx=abs(st[p].lazy[i]);
      bool incremental=st[p].lazy[i]>0;
      if(incremental){
	inc(st,2*p,L,mid,xx);
	inc(st,2*p+1,mid+1,R,xx);
      }else{
	dec(st,2*p,L,mid,xx);
	dec(st,2*p+1,mid+1,R,xx);	
      }
    }
    st[p].lazy.clear();
  }
}

void update(Node *st, int p, int L, int R, int x, int y,bool incremental) {
  if (y < L || R < x) {
    return;
  }
  if (x<=L && R <= y) {
    if (incremental)
      inc(st,p,L,R,x);
    else
      dec(st,p,L,R,x);
    if(L==R)
      st[p].lazy.clear();
    return;
  }
  propagate(st,p,L,R);
  int mid=(L+R)/2;
  update(st,2*p,L,mid,x,y,incremental);
  update(st,2*p+1,mid+1,R,x,y,incremental);
  st[p].sum=(st[2*p].sum+st[2*p+1].sum)%MOD;
}

ll query(Node *st, int p, int L,int R, int x, int y) {
  if (y < L || R < x) {
    return 0;
  }
  if (x<=L && R <= y) {
    return st[p].sum;
  }
  propagate(st,p,L,R);
  
  int mid=(L+R)/2;
  
  ll ans1=query(st, 2*p ,L    ,mid,x,y);
  ll ans2=query(st,2*p+1,mid+1,R  ,x,y);
  
  return (ans1+ans2)%MOD;
}

ll sub(ll a, ll b){
  ll ans=b-a;
  if(ans<0)ans+=MOD;
  return ans*100000%MOD;
}

int main() {
  calc_sum();

  // const int head[]={1,554,1,1,999};
  // const int tail[]={1,19947,100000,10485,20000};

  // for (int i=0;i<sizeof(head)/sizeof(head[0]);i++){
  //   printf("%lld\n",sub(sum[head[i]-1],sum[tail[i]]));
  // }
  // puts("");


  scanf("%d%d", &n, &q);
  init(st,1,1,n);
  int sym, x, y;
  for (int i = 1; i <= q; i++) {
    scanf("%d%d%d", &sym, &x, &y);
    if(sym==0){
      printf("%lld\n",query(st,1,1,n,x,y));
    }else if(sym==1){
      update(st,1,1,n,x,y,true);
    }else{
      update(st,1,1,n,x,y,false);
    }
  }
  return 0;
}
