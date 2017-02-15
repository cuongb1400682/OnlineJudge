#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;

#define N 1024

int clr[N],p[N],n,m;
vector<int> G[N],left;
bool vis[N];

void dfs1(int u){
    if(clr[u]==1) left.push_back(u);
    for(int i=0;i<(int)G[u].size();i++){
        int v=G[u][i];
        if(clr[v]==0){
            clr[v]=-clr[u];
            dfs1(v);            
        }
    }
}

int dfs(int u){
    if(vis[u]||clr[u]==-1)return 0;
    vis[u]=true;
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
    int t,no=0;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<=n;i++){
            G[i].clear();
        }
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        memset(clr,0,sizeof(clr));
        left.clear();
        for(int u=1;u<=n;u++)
            if(clr[u]==0){
                clr[u]=1;
                dfs1(u);
            }
        memset(p,-1,sizeof(p));
        int ans=0;
        for(int i=0;i<(int)left.size();i++){
            int u=left[i];
            memset(vis,0,sizeof(vis));
            ans+=dfs(u);
        }
        printf("Case %d: %d\n",++no,n-ans);
    }
    return 0;
}
