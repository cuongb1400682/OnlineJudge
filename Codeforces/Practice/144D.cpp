#include <stdio.h>
#include <string.h>
#include <set>

using namespace std;

typedef pair<int,int> ii;

#define SZ 100005
#define INF 0x3f3f3f3f

int d[SZ],n,m,s,l;
set<ii> G[SZ];
set<int> T[SZ];

void dijkstra(){
  set<ii> q;
  memset(d,0x3f,sizeof(d));
  d[s]=0;
  q.insert(ii(0,s));
  while(!q.empty()){
    int u=q.begin()->second;
    q.erase(q.begin());
    for(set<ii>::iterator it=G[u].begin();it!=G[u].end();it++){
      int v=it->first;
      int w=it->second;
      if(d[v]>d[u]+w){
        if(d[v]!=INF)
          q.erase(q.find(ii(d[v],v)));
        d[v]=d[u]+w;
        q.insert(ii(d[v],v));
      }
    }
  }
}

int main(){
  scanf("%d%d%d",&n,&m,&s);
  for(int i=0;i<m;i++){
    int u,v,w;
    scanf("%d%d%d",&u,&v,&w);
    G[u].insert(ii(v,w));
    G[v].insert(ii(u,w));
  }
  scanf("%d",&l);
  dijkstra();
  int ans=0;
  for(int u=1;u<=n;u++){
    for(set<ii>::iterator it=G[u].begin();it!=G[u].end();it++){
      int v=it->first;
      if(T[u].count(v)>0)
        continue;
      int w=it->second;
      int d1=l-d[u];
      int d2=l-d[v];
      if(d1<0&&d2<0)
        continue;
      if(d1>0&&d2>0){
        if(d1+d2==w){
          ans++;
        }else if(d1+d2<w){
          ans+=2;
        }
      }else if(d1>0&&d1<w){
        ans++;
      }else if(d2>0&&d2<w){
        ans++;
      }
      T[u].insert(v);T[v].insert(u);
    }
    if(d[u]==l)
      ans++;
  }
  printf("%d\n",ans);
  return 0;
}
