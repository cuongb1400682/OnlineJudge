#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

#define N 500
#define M 100000
#define INF 0x3f3f3f3f

struct Edge{
    int u,v,c,nxt;
    Edge(int u=0,int v=0,int c=0,int nxt=-1):
        u(u),v(v),c(c),nxt(nxt){}
};

struct Stone{
    char size[2];
    int dist;
};

int n,d,n_edge,s,t,dist[150][150],flow[M];
Edge edge[M];
int head[N];
Stone stone[N];

void connect(int u,int v,int w){
    //printf("%d %d %d\n",u,v,w);
    edge[n_edge++]=Edge(u,v,w,head[u]);
    head[u]=n_edge-1;
    edge[n_edge++]=Edge(v,u,0,head[v]);
    head[v]=n_edge-1;
}

int ffa(int lim){
    int p[N],f[N],ans=0;
    memset(flow,0,sizeof(flow));
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
                if(dist[u>>1][e.v>>1]>lim)
                    continue;
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
            if(edge[i].c!=INF){
                flow[i]+=f[t];
                flow[i^1]-=f[t];
            }
        }
        ans++;
        if(ans>=2)break;
    }
    return ans;
}

void readf(){
    scanf("%d%d",&n,&d);
    n_edge=0;
    memset(head,-1,sizeof(head));
    memset(dist,0,sizeof(dist));
    for(int i=1;i<=n;i++)
        scanf("%1s-%d",stone[i].size,&stone[i].dist);
    stone[0].dist=0;
    stone[n+1].dist=d;
    for(int i=1;i<=n+1;i++)
        dist[i][i-1]=dist[i-1][i]=stone[i].dist-stone[i-1].dist;
    for(int i=2;i<=n+1;i++)
        for(int x=0,y=i;x<=n+1&&y<=n+1;x++,y++)
            dist[y][x]=dist[x][y]=dist[x][y-1]+dist[y-1][y];
    for(int i=1;i<=n;i++){
        connect(2*i,2*i+1,stone[i].size[0]=='B'?INF:1);
        connect(2*i+1,2*i,stone[i].size[0]=='B'?INF:1);
    }
    for(int i=1;i<=n-1;i++)
        for(int j=i+1;j<=n;j++){
            connect(2*i+1,2*j,INF);
            connect(2*j+1,2*i,INF);
        }
    s=1;
    t=2*n+2;
    for(int i=1;i<=n;i++){
        connect(s,2*i,INF);
        connect(2*i+1,t,INF);
    }
    connect(s,t,INF);
}

int solve(){
    int ans=0;
    for(int l=0,r=d+1;l<=r;){
        int mid=(l+r)>>1;
        if(ffa(mid)>=2){
            ans=mid;
            r=mid-1;
        }else{
            l=mid+1;
        }
    }
    return ans;
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        readf();
        printf("Case %d: %d\n",no,solve());
    }
    return 0;
}
