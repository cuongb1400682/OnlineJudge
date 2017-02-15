#include<stdio.h>
#include<vector>

using namespace std;

#define SZ 505

struct DSU{
    int p[SZ],n_comp;
};

int n,m,k;
DSU pre[10005],suf[10005];
bool dbg;
pair<int,int> e[10005];

int get_root(DSU &dsu,int u){
    if(dsu.p[u]==u)
        return u;
    else
        return dsu.p[u]=get_root(dsu,dsu.p[u]);
}

void join(DSU &dsu,int u,int v){
    int r=get_root(dsu,u);
    int s=get_root(dsu,v);
    if(r!=s){
        dsu.n_comp--;
        dsu.p[r]=s;
    }
}

void init(DSU &dsu){
    for(int u=1;u<=n;u++)
        dsu.p[u]=u;
    dsu.n_comp=n;
}

int main(){
    scanf("%d%d",&n,&m);

    init(pre[0]);
    init(suf[m+1]);

    for(int i=1;i<=m;i++){
        scanf("%d%d",&e[i].first,&e[i].second);
        pre[i]=pre[i-1];
        join(pre[i],e[i].first,e[i].second);
    }

    for(int i=m;i>=1;i--){
        suf[i]=suf[i+1];
        join(suf[i],e[i].first,e[i].second);
    }

    scanf("%d",&k);
    for(int i=1;i<=k;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        DSU ans=pre[u-1];
        for(int u=1;u<=n;u++){
            int r=get_root(ans,u);
            int s=get_root(suf[v+1],u);
            join(ans,r,s);
        }
        printf("%d\n",ans.n_comp);
    }
    return 0;
}
