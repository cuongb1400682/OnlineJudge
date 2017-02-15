#include<stdio.h>
#include<set>
#include<string.h>
using namespace std;

#define N 250
#define M 50000
#define INF 0x3f3f3f3f

typedef pair<int,int> ii;

struct Edge{
  int u,v,c,nxt,w;
    Edge(int u=0,int v=0,int c=0,int nxt=-1,int w=0):
        u(u),v(v),c(c),nxt(nxt),w(w){}
};

Edge edge[M];
int flow[M],n_edge,head[N],n,m,s,t,k;

void connect(int u,int v,int w){
    edge[n_edge++]=Edge(u,v,1,head[u],w);
    head[u]=n_edge-1;
    edge[n_edge++]=Edge(v,u,0,head[v],w);
    head[v]=n_edge-1;
}

void readf(){
    scanf("%d%d",&n,&m);
    n_edge=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++)
        connect(2*i,2*i+1,1);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        if(u>v)swap(u,v);
        connect(2*u+1,2*v,w);
    }
    scanf("%d",&k);
    s=1;
    t=2*n+2;
}

void dijkstra(int *p,int *d){
    set<ii> q;
    bool vis[N];
    for(int u=1;u<=2*n+2;u++){
        d[u]=INF;
        p[u]=-1;
        vis[u]=false;
    }
    d[s]=0;
    q.insert(ii(0,s));
    while(!q.empty()){
        int u=q.begin()->second;
        q.erase(q.begin());
        vis[u]=true;
        if(u==t)
            break;
        for(int i=head[u];i!=-1;i=edge[i].nxt){
            Edge e=edge[i];
            if(e.v!=s&&e.c>flow[i])
                if(d[e.v]>e.w&&!vis[e.v]){
                    if(d[e.v]!=INF)
                        q.erase(q.find(ii(d[e.v],e.v)));
                    d[e.v]=e.w;
                    p[e.v]=i;
                    q.insert(ii(d[e.v],e.v));
                }
        }
    }
}

int ffa(){
    int ans=-INF,p[N],d[N];
    memset(flow,0,sizeof(flow));
    for(int i=1;i<=k;i++){
        dijkstra(p,d);
        if(p[t]==-1)
            return -1;
        int max_w=-INF;
        for(int i=p[t];i!=-1;i=p[edge[i].u])
            if(edge[i].w!=INF&&max_w<edge[i].w)
                max_w=edge[i].w;
        for(int i=p[t];i!=-1;i=p[edge[i].u]){
            flow[i]+=1;
            flow[i^1]-=1;
        }
        ans=max(ans,max_w);
    }
    return ans;
}

int main(){
    int no=0,n_case;
    scanf("%d",&n_case);
    while(n_case--){
        readf();
        printf("Case %d:",++no);
        int ans=ffa();
        if(ans<0)
            puts(" no solution");
        else
            printf(" %d\n",ans);
    }
    return 0;
}
