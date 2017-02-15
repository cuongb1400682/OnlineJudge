#include <stdio.h>
#include <string.h>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define M 2001
#define N 1001
#define INF 0x3f3f3f3f

struct Edge{
  int u,v,w;
};

Edge e[M];
vector<int> G[N],comp[N],V[N];
int n,m,num[N],low[N],label,n_comp,p[N],d[N];
bool vis[N];
stack<int> stk;

void tarjan(int u,int &label){
  num[u]=low[u]=++label;
  stk.push(u);vis[u]=true;
  for(int i=0;i<(int)G[u].size();i++){
    int v=G[u][i];
    if(num[v]==0){
      tarjan(v,label);
      low[u]=min(low[u],low[v]);
    }else if(vis[v]){
      low[u]=min(low[u],num[v]);
    }
  }

  if(num[u]==low[u]){
    n_comp++;
    while(stk.top()!=u){
      vis[stk.top()]=false;
      p[stk.top()]=n_comp;
      stk.pop();      
    }
    vis[u]=false;
    p[u]=n_comp;
    stk.pop();
  }
}

void split(){
  label=0;
  n_comp=-1;
  stk=stack<int>();
  for(int u=0;u<n;u++){
    num[u]=low[u]=0;
    vis[u]=false;
    comp[u].clear();
    V[u].clear();
    p[u]=-1;
  }
  for(int u=0;u<n;u++)
    if(p[u]==-1)
      tarjan(u,label);
  for(int i=0;i<m;i++){
    if(p[e[i].u]==p[e[i].v])
      comp[p[e[i].u]].push_back(i);
  }
  for(int i=0;i<n;i++)
    V[p[i]].push_back(i);

  for(int u=0;u<=n_comp;u++){
    sort(comp[u].begin(),comp[u].end());
    comp[u].resize(unique(comp[u].begin(),comp[u].end())-comp[u].begin());
    sort(V[u].begin(),V[u].end());
    V[u].resize(unique(V[u].begin(),V[u].end())-V[u].begin());
  }
}

void readf(){
  scanf("%d%d",&n,&m);
  for(int u=0;u<n;u++) G[u].clear();
  for(int i=0;i<m;i++){
    scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    G[e[i].u].push_back(e[i].v);
  }
}

void solve(){
  memset(vis,0,sizeof(vis));
  for(int c=0;c<=n_comp;c++){
    vector<int> &edge=comp[c];
    vector<int> &vertex=V[c];

    if(edge.size()<2||vertex.size()<2) continue;
    
    for(int i=0;i<(int)vertex.size();i++)
      d[vertex[i]]=INF;
    d[vertex[0]]=0;
    
    for(int i=1;i<=(int)vertex.size()-1;i++){
      for(int j=0;j<(int)edge.size();j++){
        int u=e[edge[j]].u,v=e[edge[j]].v,w=e[edge[j]].w;
        if(d[v]>d[u]+w)
          d[v]=d[u]+w;
      }
    }

    for(int j=0;j<(int)edge.size();j++){
      int u=e[edge[j]].u,v=e[edge[j]].v,w=e[edge[j]].w;
      if(d[v]>d[u]+w){
        vis[c]=true;
        break;
      }
    }
  }

  bool found;
  do{
    found=false;
    for(int j=0;j<m;j++)
      if(p[e[j].u]!=p[e[j].v]&&vis[p[e[j].v]]&&!vis[p[e[j].u]])
        vis[p[e[j].u]]=true,found=true;
  }while(found);

  static int no=0;
  found=false;
  printf("Case %d:",++no);
  for(int u=0;u<n;u++)
    if(vis[p[u]])
      printf(" %d",u),found=true;
  if(!found)printf(" impossible");
  printf("\n");
}

int main(){
  int nTest;
  scanf("%d",&nTest);
  while(nTest--){
    readf();
    split();
    solve();
  }
  return 0;
}
