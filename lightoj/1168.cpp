#include<stdio.h>
#include<vector>
#include<stack>
using namespace std;

#define N 1024

int num[N],low[N],n_lab,p[N],n_cmp,n,lab[N],m,in[N],out[N];
bool vis[N],yes;
stack<int> stk;
vector<int> G[N];

void init(){
  n_lab=0;
  n_cmp=0;
  m=0;
  yes=false;
  for(int u=0;u<N;u++){
    num[u]=0;
    low[u]=0;
    p[u]=-1;
    lab[u]=-1;
    in[u]=0;
    out[u]=0;
    vis[u]=false;
    G[u].clear();
  }
}

void tarjan(int u){
  num[u]=low[u]=++n_lab;
  vis[u]=true;stk.push(u);
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(num[v]==0){
      tarjan(v);
      low[u]=min(low[u],low[v]);
    }else if(vis[v]){
      low[u]=min(low[u],num[v]);
    }
  }
  if(low[u]==num[u]){
    while(stk.top()!=u){
      vis[stk.top()]=false;
      p[stk.top()]=n_cmp;
      stk.pop();
    }
    vis[u]=false;
    p[u]=n_cmp;
    stk.pop();    
    n_cmp++;
  }
}

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d",&n);
    init();
    for(int i=0,k;i<n;i++){
      scanf("%d",&k);
      while(k--){
        int u,v;
        scanf("%d%d",&u,&v);
        
        if(lab[u]==-1)lab[u]=m++;
        if(lab[v]==-1)lab[v]=m++;        
        u=lab[u],v=lab[v];
        G[u].push_back(v);
      }
    }
    yes=true;
    if(lab[0]==-1)
      yes=false;
    else{
      for(int u=0;u<m;u++)
        if(num[u]==0)
          tarjan(u);
      for(int u=0;u<m;u++)
        for(int i=0;i<(int)G[u].size();i++){
          int v=G[u][i];
          if(p[u]!=p[v])
            in[p[v]]++,out[p[u]]++;
        }
      yes=(in[p[lab[0]]]==0);
      int out_0=0,out_1=0,in_0=0,in_1=0;
      for(int u=0;yes&&u<n_cmp;u++){
        out_0+=(out[u]==0);
        out_1+=(out[u]==1);
        in_0+=(in[u]==0);
        in_1+=(in[u]==1);
      }
      yes=yes&&(out_0==1&&out_1==n_cmp-1&&in_0==1&&in_1==n_cmp-1);
    }
    printf("Case %d: %s\n",++no,yes?"YES":"NO");
  }
  return 0;
}
