#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;

#define N 100

bool vis[N],usableX[N],usableY[N];
vector<int> G[N],X[N],Y[N];
int n,m,p[N],nNode;
char grid[N][N];

int dfs(int u){
    if(vis[u]||!usableX[u])return 0;
    vis[u]=true;
    for(int i=0;i<(int)G[u].size();i++){
        int v=G[u][i];
        if(!usableY[v])continue;
        if(p[v]==-1||dfs(p[v])){
            p[v]=u;
            return 1;
        }
    }
    return 0;
}

int hopcroftKarp(){
    int ans=0;
    memset(p,-1,sizeof(p));
    for(int u=1;u<=n;u++){
        if(!usableX[u])continue;
        memset(vis,0,sizeof(vis));
        ans+=dfs(u);
    }
    return ans;
}

int solve(){
    int ans=0;
    for(int u=1;u<=n;u++)
        for(int v=1;v<=m;v++){
            if(grid[u][v]=='0')continue;
            nNode=0;
            memset(usableX,0,sizeof(usableX));
            memset(usableY,0,sizeof(usableY));
            for(int i=0;i<(int)X[u].size();i++)
                nNode+=(usableY[X[u][i]]=true);
            for(int i=0;i<(int)Y[v].size();i++)
                nNode+=(usableX[Y[v][i]]=true);
            ans=max(ans,nNode-hopcroftKarp());
        }
    return ans;
}

int main(){
    int t,no=0;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<N;i++){
            G[i].clear();
            X[i].clear();
            Y[i].clear();
        }
        for(int i=1;i<=n;i++){
            scanf("%s",grid[i]+1);
            for(int j=1;j<=m;j++)
                if(grid[i][j]=='0'){
                    G[i].push_back(j);
                }else{
                    X[i].push_back(j);
                    Y[j].push_back(i);
                }
        }
        printf("Case %d: %d\n",++no,solve());
    }
    return 0;
}
