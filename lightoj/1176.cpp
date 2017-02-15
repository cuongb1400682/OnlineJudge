#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;

#define N 60

bool vis[N];
vector<int> G[N];
int n,m,p[N];

int sz2i(const char *p){
    static const char *s[]={"XS","XXL","XL","L","M","S"};
    for(int i=0;i<=5;i++)
        if(strcmp(s[i],p)==0)
            return i;
    return -1;
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
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
            G[i].clear();
        for(int i=1;i<=m;i++){
            char size1[5],size2[5];
            scanf("%s%s",size1,size2);
            int y1=sz2i(size1);
            int y2=sz2i(size2);
            for(int j=1;j<=n;j++){
                G[i].push_back(y1); 
                G[i].push_back(y2);
                y1+=7;
                y2+=7;
            }
        }
        memset(p,-1,sizeof(p));
        int ans=0;
        for(int u=1;u<=m;u++){
            memset(vis,0,sizeof(vis));
            ans+=dfs(u);
        }
        printf("Case %d: %s\n",no,ans==m?"YES":"NO");
    }
    return 0;
}
