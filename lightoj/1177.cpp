#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;

#define N 205
#define M N*N
#define INF 0x3f3f3f3f

struct Edge{
    int u,v,c,f,nxt,rev;
    Edge(int _u=0,int _v=0,int _c=0,int _nxt=-1):
        u(_u),v(_v),c(_c),f(0),nxt(_nxt),rev(-1){}
};

vector<Edge> edge;
int head[2*N+2],s,t,n,m;

void connect(int u,int v,int w){
    edge.push_back(Edge(u,v,w,head[u]));
    head[u]=edge.size()-1;
    edge.push_back(Edge(v,u,0,head[v]));
    head[v]=edge.size()-1;
    edge[head[u]].rev=head[v];
    edge[head[v]].rev=head[u];
}

int ffa(){
    int ans=0,p[N],f[N];
    while(1){
        queue<int> q;
        q.push(s);
        memset(p,-1,sizeof(p));
        f[s]=INF;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=head[u];i!=-1;i=edge[i].nxt){
                Edge e=edge[i];
                if(e.v!=s&&p[e.v]==-1&&e.c>e.f){
                    p[e.v]=i;
                    f[e.v]=min(f[u],e.c-e.f);
                    q.push(e.v);
                    if(e.v==t)
                        goto augment;
                }
            }
        }
      augment:
        if(p[t]==-1)
            break;
        for(int i=p[t];i!=-1;i=p[edge[i].u]){
            int j=edge[i].rev;
            edge[i].f+=f[t];
            edge[j].f-=f[t];
        }
        ans+=f[t];
    }
    return ans;
}

void readf(){
    int u,v,w;
    scanf("%d%d",&n,&m);
    s=2,t=2*n+1;
    edge.clear();
    memset(head,-1,sizeof(head));
    connect(2,3,INF);
    connect(t-1,t,INF);
    for(int u=2;u<=n-1;u++){
        scanf("%d",&w);
        connect(2*u,2*u+1,w);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        connect(2*u+1,2*v,w);
        connect(2*v+1,2*u,w);
    }
}

int main(){
    int n_case,no=0;
    scanf("%d",&n_case);
    while(n_case--){
        readf();
        printf("Case %d: %d\n",++no,ffa());
    }
    return 0;
}
