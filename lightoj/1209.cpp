#include<stdio.h>
#include<string.h>
#include<list>
using namespace std;

#define N 512

struct Voter{
    int u,v;
};

list<int> G[N];
Voter fvt[N],mvt[N];
int m,p[N],k1,k2;
bool vis[N];

int dfs(int u){
    if(vis[u])return 0;
    vis[u]=true;
    for(list<int>::iterator it=G[u].begin();it!=G[u].end();it++)
        if(p[*it]==-1||dfs(p[*it])){
            p[*it]=u;
            return 1;
        }
    return 0;
}

int main(){
    int nTest,no=0;
    scanf("%d",&nTest);
    while(nTest--){
        scanf("%*d%*d%d",&m);
        for(int i=0;i<=m;i++)
            G[i].clear();
        k1=k2=0;
        for(int i=1;i<=m;i++){
            char a[10],b[10];
            scanf(" %s %s ",a,b);
            if(*a=='M'){
              ++k1;
                sscanf(a+1,"%d",&mvt[k1].u);
                sscanf(b+1,"%d",&mvt[k1].v);
            }else{
                ++k2;              
                sscanf(a+1,"%d",&fvt[k2].u);
                sscanf(b+1,"%d",&fvt[k2].v);
            }
        }
        for(int i=1;i<=k1;i++)
            for(int j=1;j<=k2;j++)
                if(mvt[i].u==fvt[j].v||mvt[i].v==fvt[j].u)
                    G[i].push_back(j);
        int ans=0;
        memset(p,-1,sizeof(p));
        for(int u=1;u<=k1;u++){
            memset(vis,0,sizeof(vis));
            ans+=dfs(u);
        }
        printf("Case %d: %d\n",++no,m-ans);
    }
    return 0;
}
