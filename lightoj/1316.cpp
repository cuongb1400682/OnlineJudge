#include<stdio.h>
#include<set>
#include<string.h>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

#define N 512
#define INF 0x3f3f3f3f

typedef pair<int,int> ii;

int n,m,s,shop[N],dp[1<<18][18],start,end,sub,a[N][N];
vector<ii> G[N];

void init(){
  memset(dp,0x3f,sizeof(dp));
  memset(a,0x3f,sizeof(a));
  start=-1;
  end=-1;
  for(int u=0;u<n;u++)
    G[u].clear();
}

void dijkstra(int u,int *d){
  set<ii> q;
  d[u]=0;
  q.insert(ii(0,u));
  while(!q.empty()){
    int u=q.begin()->second;
    q.erase(q.begin());
    for(int i=0;i<(int)G[u].size();i++){
      int v=G[u][i].first,w=G[u][i].second;
      if(d[v]>d[u]+w){
        if(d[v]!=INF)
          q.erase(q.find(ii(d[v],v)));
        d[v]=d[u]+w;
        q.insert(ii(d[v],v));
      }
    }
  }
}

void spfa(int u,int *d){
  queue<int> q;
  bool vis[N]={false};
  d[u]=0;
  q.push(u);vis[u]=true;
  while(!q.empty()){
    u=q.front();
    vis[u]=false;
    q.pop();
    for(int i=0;i<(int)G[u].size();i++){
      int v=G[u][i].first,w=G[u][i].second;
      if(d[v]>d[u]+w){
        d[v]=d[u]+w;
        if(!vis[v])
          q.push(v),vis[v]=true;
      }
    }
  }
}

int at(int st,int u){
  return (st>>u)&1;
}

int cnt_bit(int x){
  int ans=0;
  while(x>0)
    x-=x&(-x),ans++;
  return ans;
}

void solve(){
  vector<ii> states;
  static int no=0;
  int mxbit=-1,midist=INF;
  for(int st=0;st<(1<<s);st++)
    states.push_back(ii(cnt_bit(st),st));
  sort(states.begin(),states.end());
  for(int i=0;i<(int)states.size();i++){
    int st=states[i].second;
    int n_bit=states[i].first;
    for(int u=0;u<s;u++){
      if(dp[st][u]>=INF)continue;
      for(int v=0;v<s;v++){
        if(a[shop[u]][shop[v]]>=INF||at(st,u)!=1&&at(st,v)!=0)
          continue;
        dp[st|(1<<v)][v]=min(dp[st|(1<<v)][v],dp[st][u]+a[shop[u]][shop[v]]);
        if(at(st,end)==1&&dp[st][end]<INF)
          if(n_bit>mxbit||(n_bit==mxbit&&dp[st][end]<midist)){
            mxbit=n_bit;
            midist=dp[st][end];
          }
      }
    }
  }
  printf("Case %d: ",++no);
  if(mxbit==-1)
    puts("Impossible");
  else
    printf("%d %d\n",mxbit-sub,midist);
}

int main(){
  int nTest;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d%d%d",&n,&m,&s);
    init();
    sub=2;
    for(int i=0;i<s;i++){
      scanf("%d",&shop[i]);
      if(shop[i]==0)start=i,sub--;
      if(shop[i]==n-1)end=i,sub--;
    }
    if(start==-1){
      shop[s]=0;
      start=s;
      s++;
    }
    if(end==-1){
      shop[s]=n-1;
      end=s;
      s++;
    }
    dp[1<<start][start]=0;
    for(int i=0;i<m;i++){
      int u,v,w;
      scanf("%d%d%d",&u,&v,&w);
      G[u].push_back(ii(v,w));
    }
    for(int u=0;u<n;u++)
      spfa(u,a[u]);
    solve();
  }
  return 0;
}
