#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

#define SZ 1000005

typedef pair<int,int> ii;

struct state{
  state(){
    x=y=i=val=0;
  }
  int x,y,i,val;
};

int p[SZ],n,m,n_st,dp[SZ];
state st[SZ];
vector<int> H,V;

bool cmp(state a,state b){
  return (a.val<b.val||(a.val==b.val&&a.i<b.i)); 
}

bool cmp2(state a,state b){
  return a.i<b.i;
}

int get_root(int u){
  return p[u]=(p[u]==u?u:get_root(p[u]));    
}

void join(int u,int v){
  if(u==v) return;
  int r=get_root(u),s=get_root(v);
  if(r!=s)
    p[s]=r;
}

int main(){
  scanf("%d%d",&n,&m);
  int n_st=0;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++){
      ++n_st;
      scanf("%d",&st[n_st].val);
      st[n_st].x=i;st[n_st].y=j;st[n_st].i=n_st;
      p[n_st]=n_st;dp[n_st]=1;
    }

  sort(st+1,st+1+n_st,cmp);

  vector<state> H_,V_;
  H_.assign(n+1,state());
  V_.assign(m+1,state());
  for(int u=1;u<=n_st;u++){
    int x=st[u].x,y=st[u].y,val=st[u].val;
    if(H_[x].val==val)
      join(H_[x].i,st[u].i);
    if(V_[y].val==val)
      join(V_[y].i,st[u].i);
    H_[x]=st[u];
    V_[y]=st[u];
  }

  H.assign(n+1,0);
  V.assign(m+1,0);
  for(int u=1,v;u<=n_st;u=v){
    for(v=u;v<=n_st;v++){
      if(st[v].val!=st[u].val) break;
      int x=st[v].x,y=st[v].y,r=get_root(st[v].i);
      dp[r]=max(dp[r],max(H[x]+1,V[y]+1));
    }
    for(v=u;v<=n_st;v++){
      if(st[v].val!=st[u].val) break;
      int x=st[v].x,y=st[v].y,r=get_root(st[v].i);
      dp[r]=max(dp[r],max(H[x]+1,V[y]+1));
    }
  }

  sort(st+1,st+1+n_st,cmp2);
  for(int i=1;i<=n_st;i++){
    printf("%d ",dp[get_root(st[i].i)]);
    if(i%m==0)
      printf("\n");
  }
  return 0;
}
