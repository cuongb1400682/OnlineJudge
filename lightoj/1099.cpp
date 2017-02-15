#include<stdio.h>
#include<set>
#include<vector>
using namespace std;

#define N 5005

typedef pair<int,int> ii;

int time[N],n,m;
vector<ii> G[N];

int dijkstra(){
  set<ii> q;
  int time[N];
  for(int u=1;u<=n;u++)
    time[u]=0;
  q.insert(ii(0,1));
  while(!q.empty()){
    int u=q.begin()->second;
    int d=q.begin()->first;
    q.erase(q.begin());
    if(time[u]>=2)continue;
    if(time[u]==1&&u==n)
      return d;    
    time[u]++;
    for(int i=0;i<(int)G[u].size();i++){
      int v=G[u][i].first,w=G[u][i].second;
      if(time[v]<2)
        q.insert(ii(d+w,v));
    }
  }
  return -1;
}

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
      G[i].clear();
    for(int i=1;i<=m;i++){
      int u,v,w;
      scanf("%d%d%d",&u,&v,&w);
      G[u].push_back(ii(v,w));
      G[v].push_back(ii(u,w));
    }
    printf("Case %d: %d\n",++no,dijkstra());
  }
  return 0;
}
