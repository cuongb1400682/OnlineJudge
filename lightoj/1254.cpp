#include<stdio.h>
#include<set>
#include<vector>
using namespace std;

#define N 101
#define INF 1000000000

typedef pair<int,int> ii;

struct State{
  int u,fuel,cost;
  State(int u=0,int f=0,int c=0):
    u(u),fuel(f),cost(c){}
};

int n,m,d[N][N],p[N];
vector<ii> G[N];

bool operator<(State a,State b){
  if(a.cost!=b.cost)
    return a.cost<b.cost;
  if(a.u!=b.u)
    return a.u<b.u;
  return a.fuel<b.fuel;
}

int dijkstra(int s,int t,int c){
  set<State> q;
  for(int u=0;u<n;u++)
    for(int f=0;f<=c;f++)
      d[u][f]=INF;
  q.insert(State(s,0,0));
  
  d[s][0]=0;
  while(!q.empty()){
    int u=q.begin()->u,f=q.begin()->fuel,cost=q.begin()->cost;
    q.erase(q.begin());
    
    for(int i=0;i<(int)G[u].size();i++){
      int v=G[u][i].first,w=G[u][i].second;
      if(f>=w&&d[v][f-w]>d[u][f]){
        if(d[v][f-w]!=INF)
          q.erase(q.find(State(v,f-w,d[v][f-w])));
        d[v][f-w]=d[u][f];
        q.insert(State(v,f-w,d[v][f-w]));
      }
    }
    if(f+1<=c&&d[u][f+1]>d[u][f]+p[u]){
      if(d[u][f+1]!=INF)
        q.erase(q.find(State(u,f+1,d[u][f+1])));
      d[u][f+1]=d[u][f]+p[u];
      q.insert(State(u,f+1,d[u][f+1]));
    }
  }

  int ans=INF;
  for(int f=0;f<=c;f++)
    if(d[t][f]<ans)
      ans=d[t][f];
  return ans==INF?-1:ans;
}

int main(){
  int nTest,no=0,ans,q;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d%d",&n,&m);
    for(int u=0;u<n;u++){
      G[u].clear();
      scanf("%d",&p[u]);
    }    
    for(int i=0;i<m;i++){
      int u,v,w;
      scanf("%d%d%d",&u,&v,&w);
      G[u].push_back(ii(v,w));
      G[v].push_back(ii(u,w));
    }
    printf("Case %d:\n",++no);
    scanf("%d",&q);
    while(q--){
      int u,v,c;
      scanf("%d%d%d",&c,&u,&v);
      ans=dijkstra(u,v,c);      
      if(ans==-1)
        puts("impossible");
      else
        printf("%d\n",ans);
    }
  }
  return 0;
}
