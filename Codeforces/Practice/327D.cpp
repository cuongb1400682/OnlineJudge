#include <stdio.h>
#include <vector>
#include <map>
#include <string.h>

using namespace std;

#define SZ 512

const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

typedef pair<int,int> ii;

int n,m;
map<ii,vector<ii> > G;
char grid[SZ][SZ];
bool vis[SZ][SZ];
vector<pair<int,ii> > ans;

void out(int o,int u,int v){
  ans.push_back(make_pair(o,ii(u,v)));
}

void fill(int u,int v){
  out('B',u,v);
  grid[u][v]='#';
  for(int i=0;i<4;i++){
    int x=u+dx[i],y=v+dy[i];
    if(x>0&&y>0&&x<=n&&y<=m&&!vis[x][y]&&grid[x][y]=='.'){
      G[ii(u,v)].push_back(ii(x,y));
      G[ii(x,y)].push_back(ii(u,v));
      fill(x,y);
    }
  }
}

void buildred(int u,int v,bool (*vis)[SZ]){
  for(int i=0;i<(int)G[ii(u,v)].size();i++){
    int x=G[ii(u,v)][i].first;
    int y=G[ii(u,v)][i].second;
    if(!vis[x][y]){
      vis[x][y]=true;
      buildred(x,y,vis);
    }
  }
  out('D',u,v);
  out('R',u,v);
}

int main(){
  scanf("%d%d",&n,&m);
  for(int u=1;u<=n;u++)
    scanf("%s",grid[u]+1);

  for(int u=1;u<=n;u++)
    for(int v=1;v<=m;v++)
      if(grid[u][v]=='.'){
        G.clear();
        fill(u,v);
        memset(vis,false,sizeof(vis));
        vis[u][v]=true;
        buildred(u,v,vis);
        ans.pop_back();
        ans.pop_back();
      }

  printf("%d\n",(int)ans.size());
  for(int i=0;i<(int)ans.size();i++)
    printf("%c %d %d\n",ans[i].first,ans[i].second.first,ans[i].second.second);
  
  return 0;
}
