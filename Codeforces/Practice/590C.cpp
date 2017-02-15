#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>

using namespace std;

#define SZ 1024
#define INF 0x3f3f3f3f

typedef pair<int,int> ii;

const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

int n,m,d[4][SZ*SZ];
char grid[SZ][SZ];
set<int> G[SZ*SZ];
bool vis[SZ*SZ];

bool valid(int x,int y){
  return x>0&&y>0&&x<=n&&y<=m&&grid[x][y]!='#';
}

int mkgraph(){
  static int lable[SZ][SZ];
  int n_label=3;
  memset(lable,-1,sizeof(lable));
  
  for(int u=1;u<=n;u++)
    for(int v=1;v<=m;v++)
      if(grid[u][v]!='#'){
        if(grid[u][v]>='1'&&grid[u][v]<='3')
          lable[u][v]=grid[u][v]=grid[u][v]-'0';
        else
          lable[u][v]=++n_label;
      }

  for(int u=1;u<=n;u++)
    for(int v=1;v<=m;v++){
      if(grid[u][v]=='#')
        continue;
      for(int i=0;i<4;i++){
        int x=u+dx[i],y=v+dy[i];
        if(valid(x,y)&&lable[u][v]!=lable[x][y]){
          G[lable[u][v]].insert(lable[x][y]);
          G[lable[x][y]].insert(lable[u][v]);
        }
      }
    }
  return n_label;
}

void bfs(int u,int *d){
  queue<ii> q;
  int w,v;
  set<int>::iterator it;
  memset(vis,false,sizeof(vis));
  q.push(ii(u,0));
  vis[u]=true;
  while(!q.empty()){
    u=q.front().first;
    w=q.front().second;
    d[u]=min(d[u],w);
    q.pop();
    for(it=G[u].begin();it!=G[u].end();it++){
      v=*it;
      if(!vis[v]){
        vis[v]=true;
        q.push(ii(v,w+1));
      }
    }
  }
}

int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++)
    scanf("%s",grid[i]+1);
  n=mkgraph();
  memset(d,0x3f,sizeof(d));
  bfs(1,d[1]);
  bfs(2,d[2]);
  bfs(3,d[3]);
  int ans=INF;
  for(int u=1;u<=n;u++)
    if(d[1][u]!=INF&&d[2][u]!=INF&&d[3][u]!=INF)
      ans=min(ans,d[1][u]+d[2][u]+d[3][u]);
  printf("%d\n",ans!=INF?ans-2:-1);
  return 0;
}
