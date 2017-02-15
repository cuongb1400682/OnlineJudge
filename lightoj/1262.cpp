#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

#define N 250
#define M 50000
#define INF 0x3f3f3f3f

struct Edge{
    int u,v,c,nxt,x,y;
    Edge(int _u=0,int _v=0,int _c=0,int _nxt=-1,int _x=-1,int _y=-1):
        u(_u),v(_v),c(_c),nxt(_nxt),x(_x),y(_y){}
};

int n,m,s,t,flow[M],head[N],n_edge;
Edge edge[M];

void connect(int u,int v,int w,int x=-1,int y=-1){
    edge[n_edge++]=Edge(u,v,w,head[u],x,y);
    head[u]=n_edge-1;
    edge[n_edge++]=Edge(v,u,0,head[v],-1,-1);
    head[v]=n_edge-1;
}

void readf(){
    int sum,in[N],out[N];
    scanf("%d%d",&m,&n);
    int delta=n+m-1;
    memset(head,-1,sizeof(head));
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
    n_edge=0;
    s=0;
    t=2*(n+m)-1;
    for(int i=1;i<=delta;i++){
        scanf("%d",&sum);
        connect(s,i,sum);
    }
    for(int i=1;i<=delta;i++){
        scanf("%d",&sum);
        connect(delta+i,t,sum);
    }
    for(int i=n;i>=1;i--)
        for(int x=1,y=i;x<=m&&y<=n;x++,y++){
            int u=x+y-1;
            int v=delta+x-y+n;
            connect(u,v,99,x,y);
            in[u]++;
            out[v]++;
        }
    for(int i=2;i<=m;i++)
        for(int x=i,y=1;x<=m&&y<=n;x++,y++){
            int u=x+y-1;
            int v=delta+x-y+n;
            connect(u,v,99,x,y);
            in[u]++;
            out[v]++;
        }
    for(int i=0;i<n_edge;i+=2){
        if(edge[i].u==s)
            edge[i].c-=in[edge[i].v];
        else if(edge[i].v==t)
            edge[i].c-=out[edge[i].u];
    }
}

void solve(){
    int p[N],f[N];
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
    }
}

void print(){
    static int no=0;
    int a[N][N];
    for(int i=0;i<n_edge;i+=2)
        if(edge[i].x!=-1&&edge[i].y!=-1)
            a[edge[i].x][edge[i].y]=flow[i]+1;
    printf("Case %d:\n",++no);
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)
            printf("%d%s",a[i][j],j==n?"\n":" ");
    }
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    while(n_case--){
        readf();
        solve();
        print();
    }
    return 0;
}
