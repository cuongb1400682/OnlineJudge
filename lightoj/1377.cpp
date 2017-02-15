#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

#define N 205
#define INF 0x3f3f3f3f

typedef pair<int,int> ii;

const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

vector<int> G[N*N];
vector<int> sstar,tstar;
int lab[N][N],m,n,nscc,nlab,dt[N*N],ds[N*N],scc[N*N],n_star;
char grid[N][N];
ii P,D,org[N*N];

bool scmp(int i,int j){
  return ds[i]<ds[j];
}

bool tcmp(int i,int j){
  return dt[i]<dt[j];
}

bool valid(int x,int y){
  return (x>=1)&&(y>=1)&&(x<=m)&&(y<=n)&&(grid[x][y]!='#');
}

int dfs(int u,int v){
  if(lab[u][v]!=-1)return lab[u][v];
  lab[u][v]=++nlab;
  org[nlab]=ii(u,v);
  scc[nlab]=nscc;  
  if(grid[u][v]=='P')P=ii(u,v);
  if(grid[u][v]=='D')D=ii(u,v);
  if(grid[u][v]=='*')n_star++;
  for(int i=0;i<4;i++){
    int x=u+dx[i],y=v+dy[i];
    if(valid(x,y))
      G[lab[u][v]].push_back(dfs(x,y));
  }
  return lab[u][v];
}

void bfs(int s,int *d,vector<int> &star){
  queue<int> q;
  bool vis[N*N];
  for(int u=1;u<=nlab;u++){
    vis[u]=false;
    d[u]=INF;
  }
  q.push(s);
  vis[s]=true;
  star.clear();
  d[s]=0;
  while(!q.empty()){
    int u=q.front();
    ii o=org[u];
    if(grid[o.first][o.second]=='*')
      star.push_back(u);
    q.pop();
    for(int i=0;i<(int)G[u].size();i++){
      int v=G[u][i];
      if(!vis[v]){
        vis[v]=true;
        q.push(v);
        d[v]=d[u]+1;
      }
    }
  }
}

int bfs_direct(int s,int t){
  queue<int> q;
  static bool vis[N*N];
  static int d[N*N];
  for(int u=1;u<=nlab;u++){
    vis[u]=false;
    d[u]=INF;
  }
  d[s]=0;
  q.push(s);
  vis[s]=true;
  while(!q.empty()){
    int u=q.front();
    q.pop();
    for(int i=0;i<(int)G[u].size();i++){
      int v=G[u][i];
      ii o=org[v];
      if(grid[o.first][o.second]=='*')
        continue;
      if(!vis[v]){
        vis[v]=true;
        d[v]=d[u]+1;
        q.push(v);
      }
    }
  }
  return d[t];
}

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d%d",&m,&n);
    for(int i=0;i<=m*n;i++)
      G[i].clear();
    for(int i=1;i<=m;i++)
      scanf("%s",grid[i]+1);
    memset(scc,-1,sizeof(scc));
    memset(lab,-1,sizeof(lab));
    n_star=0;
    sstar.clear();
    tstar.clear();
    P=ii(-1,-1);
    D=ii(-1,-1);
    nlab=0;
    nscc=0;
    for(int i=1;i<=m;i++)
      for(int j=1;j<=n;j++)
        if(lab[i][j]==-1){
          nscc++;
          dfs(i,j);
        }
    printf("Case %d: ",++no);
    if(P==ii(-1,-1)){
      puts("impossible");
      continue;
    }
    int ans=INF;
    int s=lab[P.first][P.second];
    int t=lab[D.first][D.second];
    bfs(s,ds,sstar);
    bfs(t,dt,tstar);
    sort(sstar.begin(),sstar.end(),scmp);
    sort(tstar.begin(),tstar.end(),tcmp);
    if(scc[s]==scc[t]){
      ans=bfs_direct(s,t);
      if(ans==INF){
        if(n_star>1){
          for(int i=0;i<(int)sstar.size();i++)
            ans=min(ans,ds[sstar[i]]+dt[sstar[i]]+2);
        }
      }
      if(sstar.size()>1){
        for(int i=0;i<(int)sstar.size();i++)
          for(int j=0;j<(int)tstar.size();j++)
            if(sstar[i]!=tstar[j])
              ans=min(ans,ds[sstar[i]]+dt[tstar[j]]+1);
      }
    }else{
      if(!sstar.empty()&&!tstar.empty())
        ans=min(ans,ds[sstar[0]]+dt[tstar[0]]+1);
    }
    
    if(ans==INF)
      puts("impossible");
    else
      printf("%d\n",ans);
    
  }
  return 0;
}
