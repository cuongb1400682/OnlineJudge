#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

#define N 250
#define M 50000
#define INF 0x3f3f3f3f

struct Edge{
    int u,v,c,nxt;
    Edge(int _u=0,int _v=0,int _c=0,int _nxt=-1):
        u(_u),v(_v),c(_c),nxt(_nxt){}
};

int m,n,s,t,flow[M],head[N],n_edge,ave;
Edge edge[M];

void connect(int u,int v,int w){
    edge[n_edge++]=Edge(u,v,w,head[u]);
    head[u]=n_edge-1;
    edge[n_edge++]=Edge(v,u,0,head[v]);
    head[v]=n_edge-1;
}

void readf(){
    int p,q,k,j;
    scanf("%d%d",&m,&n);
    n_edge=0;
    memset(head,-1,sizeof(head));
    s=0;
    t=m+n+1;
    ave=0;
    for(int i=1;i<=m;i++){
        scanf("%d",&p);
        connect(s,i,p);
        ave+=p;
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&q);
        connect(m+i,t,q);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&k);
        while(k--){
            scanf("%d",&j);
            connect(i,m+j,INF);
        }
    }
}

int ffa(){
    int f[N],p[N],ans=0;
    memset(flow,0,sizeof(flow));
    while(1){
        queue<int> q;
        q.push(s);
        f[s]=INF;
        memset(p,-1,sizeof(p));
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=head[u];i!=-1;i=edge[i].nxt){
                Edge e=edge[i];
                if(e.v!=s&&p[e.v]==-1&&e.c>flow[i]){
                    p[e.v]=i;
                    f[e.v]=min(f[u],e.c-flow[i]);
                    if(e.v==t)
                        goto augment;
                    q.push(e.v);
                }
            }
        }
      augment:
        if(p[t]==-1)
            break;
        for(int i=p[t];i!=-1;i=p[edge[i].u]){
            flow[i]+=f[t];
            flow[i^1]-=f[t];
        }
        ans+=f[t];
    }
    return ans;
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        readf();
        printf("Case %d: %d\n",no,ave-ffa());
    }
    return 0;
}
