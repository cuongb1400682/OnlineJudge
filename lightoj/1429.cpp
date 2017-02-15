#include<stdio.h>
#include<vector>
#include<queue>
#include<stack>
#include<string.h>
using namespace std;

#define N 1005
#define M 10005

int low[N],num[N],cmp[N],p[N],in[N],n_lab,n_cmp,n,m;
vector<int> G[N],G2[N],G3[N];
stack<int> stk;
bool vis[N];

void tarjan(int u){
    low[u]=num[u]=++n_lab;
    stk.push(u);vis[u]=true;
    for(int i=0;i<(int)G[u].size();i++){
        int v=G[u][i];
        if(num[v]==0){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(vis[v]){
            low[u]=min(low[u],num[v]);            
        }
    }
    if(num[u]==low[u]){
        n_cmp++;
        while(vis[u]){
            cmp[stk.top()]=n_cmp;
            vis[stk.top()]=false;
            stk.pop();
        }
    }
}

void bfs(int s){
    queue<int> q;
    memset(vis,0,sizeof(vis));
    q.push(s);vis[s]=true;
    while(!q.empty()){
        int u=q.front();
        if(u!=s)
            G3[s].push_back(u);
        q.pop();
        for(int i=0;i<(int)G2[u].size();i++){
            int v=G2[u][i];
            if(vis[v])continue;
            vis[v]=true;
            q.push(v);
        }
    }
}

int dfs(int u){
    if(vis[u])return 0;
    vis[u]=true;
    for(int i=0;i<(int)G3[u].size();i++){
        int v=G3[u][i];
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
        for(int u=1;u<=n;u++){
            G[u].clear();
            G2[u].clear();
            G3[u].clear();
        }
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
        }

        memset(num,0,sizeof(num));
        memset(low,0,sizeof(low));
        memset(cmp,0,sizeof(cmp));
        n_lab=0;
        n_cmp=0;
        for(int u=1;u<=n;u++)
            if(num[u]==0)
                tarjan(u);
        
        for(int u=1;u<=n;u++)
            for(int i=0;i<(int)G[u].size();i++){
                int v=G[u][i];
                if(cmp[u]!=cmp[v])
                    G2[cmp[u]].push_back(cmp[v]);
            }

        for(int u=1;u<=n_cmp;u++)
            bfs(u);

        int ans=0;
        memset(p,-1,sizeof(p));
        memset(in,0,sizeof(in));
        for(int u=1;u<=n_cmp;u++){
            memset(vis,0,sizeof(vis));
            ans+=dfs(u);
        }
        
        printf("Case %d: %d\n",++no,n_cmp-ans);
    }
    return 0;
}
