#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define SZ 3005

typedef pair<int,int> ii;

vector<int> G[SZ];
vector<ii> G_in[SZ],G_ou[SZ];
int n,m,d[SZ][SZ];

void bfs(int s){
  queue<int> q;
  bool vis[SZ]={0};
  q.push(s);
  vis[s]=true;
  d[s][s]=0;
  while(!q.empty()){
    int u=q.front();q.pop();
    for(int i=0;i<(int)G[u].size();i++){
      int v=G[u][i];
      if(!vis[v]){
        vis[v]=true;
        d[s][v]=d[s][u]+1;
        q.push(v);
      }
    }
  }
}

void opt(int u,int v,int &a,int &w1,int &b,int &w2){
  vector<ii>::reverse_iterator it,jt;
  a=w1=b=w2=-1;
  for(it=G_in[u].rbegin();it!=G_in[u].rend();it++){
    for(jt=G_ou[v].rbegin();jt!=G_ou[v].rend();jt++){
      a=it->second,w1=it->first;
      b=jt->second,w2=jt->first;
      if(u!=a&&u!=b&&v!=a&&v!=b&&a!=b)
        return;
    }
  }
}

int main(){
  scanf("%d%d",&n,&m);
  for(int i=1,u,v;i<=m;i++){
    scanf("%d%d",&u,&v);
    if(u==v) continue;
    G[u].push_back(v);
  }

  for(int u=1;u<=n;u++){
    sort(G[u].begin(),G[u].end());
    G[u].resize(unique(G[u].begin(),G[u].end())-G[u].begin());
  }

  memset(d,-1,sizeof(d));
  for(int u=1;u<=n;u++)
    bfs(u);

  for(int u=1;u<=n;u++)
    for(int v=1;v<=n;v++){
      if(d[u][v]==-1||u==v) continue;
      G_ou[u].push_back(ii(d[u][v],v));
      G_in[v].push_back(ii(d[u][v],u));
    }

  for(int u=1;u<=n;u++){
    sort(G_in[u].begin(),G_in[u].end());
    sort(G_ou[u].begin(),G_ou[u].end());
  }

  int ans=-1;
  ii t1,t2;
  for(int u=1;u<=n;u++)
    for(vector<ii>::iterator it=G_ou[u].begin();it!=G_ou[u].end();it++){
      int v=it->second,w=it->first,a,b,w1,w2;
      opt(u,v,a,w1,b,w2);
      if(u<0) continue;
      if(w1+w+w2>ans){
        ans=w1+w+w2;
        t1=ii(a,u);
        t2=ii(v,b);
      }
    }

  printf("%d %d %d %d\n",t1.first,t1.second,t2.first,t2.second);

  return 0;
}


