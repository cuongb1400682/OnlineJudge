#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define SZ 100005
#define INF 1000000000

typedef pair<int,int> ii;

vector<ii> S,ans;
int tr[SZ],f[SZ];
int adj[128][128];

int change(int W){
  if(W<0)
    return INF;
  if(W==0)
    return 1;
  if(f[W]!=-1)
    return f[W];
  int ans=INF;
  for(int i=0;i<(int)S.size();i++){
    int tmp=change(W-S[i].second)+1;
    if(tmp<ans){
      ans=tmp;
      tr[W]=i;
    }
  }
  return f[W]=ans;
}

int main(){
  int k;
  scanf("%d",&k);

  int n=0;
  for(int i=3;i<=100;i++){
    int n_triangle=(i*(i-1)*(i-2))/6;
    if(n_triangle>k)
      break;
    n=i;
  }

  int m=k-(n*(n-1)*(n-2))/6;

  for(int u=1;u<=n-1;u++)
    for(int v=u+1;v<=n;v++)
      ans.push_back(ii(u,v));

  int z;
  if(m>0){
    for(int i=2;i<=n;i++)
      S.push_back(ii(i,(i*(i-1))/2));
    memset(f,-1,sizeof(f));
    memset(tr,0,sizeof(tr));
    change(m);
    z=n;
    for(int u=m;u>0;u-=S[tr[u]].second){
      z++;
      for(int v=1;v<=S[tr[u]].first;v++)
        ans.push_back(ii(v,z));
    }
  }

  memset(adj,0,sizeof(adj));
  for(int i=0;i<(int)ans.size();i++){
    int u=ans[i].first;
    int v=ans[i].second;
    adj[u][v]=1;
    adj[v][u]=1;
  }

  printf("%d\n",z);
  for(int u=1;u<=z;u++){
    for(int v=1;v<=z;v++)
      printf("%d",adj[u][v]);
    printf("\n");
  }

  return 0;
}
