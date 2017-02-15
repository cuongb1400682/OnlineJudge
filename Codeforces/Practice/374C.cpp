#include <stdio.h>
#include <string.h>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define SZ 1024

const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

typedef pair<int,int> ii;

int n,m,cnt[SZ][SZ];
bool vis[SZ][SZ],on_stk[SZ][SZ],has_circle;
vector<ii> src;
char grid[SZ][SZ];

bool valid(int x,int y){
  return x>0&&y>0&&x<=n&&y<=m;
}

bool is_adj(char a,char b){
  const char *p="DIMAD";
  for(int i=0;i<=3;i++)
    if(p[i]==a&&p[i+1]==b)
      return true;
  return false;
}

int dfs(int x,int y){
  cnt[x][y]=1;
  on_stk[x][y]=true;
  for(int i=0;i<4;i++){
    int u=x+dx[i],v=y+dy[i];
    if(valid(u,v)&&is_adj(grid[x][y],grid[u][v])){
      if(on_stk[u][v]){
        has_circle=true;
        return 0;
      }        
      if(!vis[u][v]){
        vis[u][v]=true;
        dfs(u,v);
        if(has_circle)
          return 0;
      }
      cnt[x][y]=max(cnt[x][y],cnt[u][v]+1);
    }
  }
  on_stk[x][y]=false;
  return cnt[x][y];
}

int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++){
    scanf("%s",grid[i]+1);
  }

  for(int u=1;u<=n;u++)
    for(int v=1;v<=m;v++){
      if(grid[u][v]!='D')
        continue;
      bool in_src=true;
      for(int i=0;i<4;i++){
        int x=u+dx[i],y=v+dy[i];
        if(valid(x,y)&&grid[x][y]=='A'){
          in_src=false;
          break;
        }
      }
      src.push_back(ii(u,v));
    }

  int ans=0;
  for(int i=0;i<(int)src.size();i++){
    int u=src[i].first,v=src[i].second;
    has_circle=false;
    ans=max(ans,dfs(u,v));
    if(has_circle){
      puts("Poor Inna!");
      return 0;
    }
  }

  if(ans/4==0)
    puts("Poor Dima!");
  else
    printf("%d\n",ans/4);
  
  return 0;
}
