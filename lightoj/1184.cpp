#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
using namespace std;

#define N 2500

struct Person{
    int h,a,m;
};

bool vis[N];
int p[N],n,m;
vector<int> G[N];
Person men[N],women[N];

bool is_adj(Person a,Person b){
    return (abs(a.h-b.h)<=12)&&(abs(a.a-b.a)<=5)&&(a.m==b.m);
}

int dfs(int u){
    if(vis[u])return 0;
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
    int nTest,no=0;
    scanf("%d",&nTest);
    while(nTest--){
        scanf("%d%d",&m,&n);
        for(int u=1;u<=m;u++)
            G[u].clear();
        for(int i=1;i<=m;i++)
            scanf("%d%d%d",&men[i].h,&men[i].a,&men[i].m);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&women[i].h,&women[i].a,&women[i].m);
        for(int i=1;i<=m;i++)
            for(int j=1;j<=n;j++)
                if(is_adj(men[i],women[j]))
                    G[i].push_back(j);
        memset(p,-1,sizeof(p));
        int ans=0;
        for(int i=1;i<=m;i++){
            memset(vis,0,sizeof(vis));
            ans+=dfs(i);
        }
        printf("Case %d: %d\n",++no,ans);
    }
    return 0;
}
