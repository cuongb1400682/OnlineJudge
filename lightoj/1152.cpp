#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;

#define N 200

typedef pair<int,int> ii;

const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

bool vis[N][N],vv[N*N];
int color[N][N],h[N][N],n,m,p[N],n_lab;
vector<int> left,right;
vector<int> G[N*N];
char grid[N][N];

void init(){
    for(int u=1;u<=n*m;u++)
        G[u].clear();
    memset(color,0,sizeof(color));
    memset(h,0,sizeof(h));
    memset(p,-1,sizeof(p));
    n_lab=0;
    left.clear();
    right.clear();
}

bool valid(int u,int v){
    return (u>=1&&u<=n)&&(v>=1&&v<=m)&&(grid[u][v]=='*');
}

void clr(int u,int v){
    if(color[u][v]==1)
        left.push_back(h[u][v]);
    if(color[u][v]==-1)
        right.push_back(h[u][v]);
    for(int i=0;i<4;i++){
        int x=u+dx[i],y=v+dy[i];
        if(valid(x,y)){
            if(color[x][y]==0){
                color[x][y]=-color[u][v];
                clr(x,y);
            }
            if(color[u][v]==1&&color[x][y]==-1)
                G[h[u][v]].push_back(h[x][y]);
        }
    }
}

int dfs(int u){
    if(vv[u])return 0;
    vv[u]=true;
    for(int i=0;i<(int)G[u].size();i++){
        int v=G[u][i];
        if(p[v]==-1||dfs(p[v])){
            p[v]=u;
            return 1;
        }
    }
    return 0;
}

int main(){
    int nTest,no=0;
    scanf("%d",&nTest);
    while(nTest--){
        scanf("%d%d",&n,&m);
        init();
        for(int i=1;i<=n;i++){
            scanf("%s",grid[i]+1);
            for(int j=1;j<=m;j++)
                if(grid[i][j]=='*')
                    h[i][j]=++n_lab;
        }
        for(int x=1;x<=n;x++)
            for(int y=1;y<=m;y++)
                if(color[x][y]==0&&grid[x][y]=='*'){
                    color[x][y]=1;
                    clr(x,y);
                }
        memset(p,-1,sizeof(p));
        int ans=0;
        for(int i=0;i<(int)left.size();i++){
            memset(vv,0,sizeof(vv));
            ans+=dfs(left[i]);
        }
        memset(vv,0,sizeof(vv));
        for(int i=0;i<(int)right.size();i++){
            if(p[right[i]]!=-1){
                vv[right[i]]=true;
                vv[p[right[i]]]=true;
            }
        }
        for(int u=1;u<=n_lab;u++)
            if(!vv[u])
                ans++;
        printf("Case %d: %d\n",++no,ans);
    }
    return 0;
}

