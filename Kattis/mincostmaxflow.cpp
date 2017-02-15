#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

#define N 300
#define INF 0x3f3f3f3f

struct Edge{
    int u,v,cost,cap,flow,i;
    Edge(int u=0,int v=0,int cost=0,int cap=0,int i=-1):
        u(u),v(v),cost(cost),cap(cap),flow(0),i(i){}
};

typedef pair<int,int> ii;

vector<Edge> edge;
int head[N],d[N],p[N],n,m,s,t,pi[N];

void connect(int u,int v,int cost,int cap){
    edge.push_back(Edge(u,v,cost,cap,head[u]));
    head[u]=edge.size()-1;
    edge.push_back(Edge(v,u,-cost,0,head[v]));
    head[v]=edge.size()-1;
}

int dijkstra(){
    priority_queue<ii,vector<ii>,greater<ii> > q;
    int f[N];
    memset(d,0x3f,sizeof(d));
    memset(p,-1,sizeof(p));
    d[s]=0;
    q.push(ii(0,s));
    f[s]=INF;
    while(!q.empty()){
        int u=q.top().second;
        int ww=q.top().first;
        q.pop();
        if(d[u]!=ww)
            continue;
        for(int i=head[u];i!=-1;i=edge[i].i){
            Edge e=edge[i];
            if(e.v!=s&&e.cap>e.flow){
                int w=e.cost+pi[u]-pi[e.v];
                if(d[e.v]>d[u]+w){
                    d[e.v]=d[u]+w;
                    p[e.v]=i;
                    f[e.v]=min(f[u],e.cap-e.flow);
                    q.push(ii(d[e.v],e.v));
                }
            }
        }
    }
    if(p[t]==-1)return 0;
    for(int u=0;u<n;u++)
        if(d[u]<INF)
            pi[u]+=d[u];
    return f[t];
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=0;i<m;i++){
        int u,v,cap,cost;
        scanf("%d%d%d%d",&u,&v,&cap,&cost);
        connect(u,v,cost,cap);
    }
    memset(pi,0,sizeof(pi));
    int mincost=0,maxflow=0;
    int f;
    while(f=dijkstra()){
        for(int i=p[t];i!=-1;i=p[edge[i].u]){
            edge[i].flow+=f;
            edge[i^1].flow-=f;
            mincost+=f*edge[i].cost;
        }
        maxflow+=f;
    }
    printf("%d %d\n",maxflow,mincost);
    return 0;
}
