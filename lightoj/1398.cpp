#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;

#define N 500
#define INF 0x3f3f3f3f

struct Edge{
    int u,v,c,f,i;
    Edge(int _u=0,int _v=0,int _c=0,int _i=-1):
        u(_u),v(_v),c(_c),f(0),i(_i){}
};

vector<Edge> edge;
int head[N],n,m,s,t,l,w,d,x[N],y[N];

void connect(int u,int v,int c){
    edge.push_back(Edge(u,v,c,head[u]));
    head[u]=edge.size()-1;
    edge.push_back(Edge(v,u,0,head[v]));
    head[v]=edge.size()-1;
}

int ffa(){
    int f[N],p[N],ans=0;
    while(true){
        f[s]=INF;
        memset(p,-1,sizeof(p));
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int u=q.front();
            if(u==t)break;
            q.pop();
            for(int i=head[u];i!=-1;i=edge[i].i){
                Edge e=edge[i];
                if(e.v!=s&&p[e.v]==-1&&e.c>e.f){
                    f[e.v]=min(f[u],e.c-e.f);
                    p[e.v]=i;
                    q.push(e.v);
                }
            }
        }
        if(p[t]==-1)break;
        for(int i=p[t];i!=-1;i=p[edge[i].u]){
            edge[i].f+=f[t];
            edge[i^1].f-=f[t];
        }
        ans+=f[t];
    }
    return ans;
}

int SS(int a,int b){
    return a*a+b*b;
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d%d%d%d",&l,&w,&n,&d);
        edge.clear();
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++)
            scanf("%d%d",&x[i],&y[i]);
        s=1;
        t=2*n+2;
        for(int i=1;i<=n;i++){
            connect(2*i,2*i+1,1);
            if(y[i]<=d)
                connect(s,2*i,1);
            if(w-y[i]<=d)
                connect(2*i+1,t,1);
            for(int j=1;j<=n;j++)
                if(SS(x[i]-x[j],y[i]-y[j])<=4*d*d)
                    connect(2*i+1,2*j,1);
        }
        printf("Case %d: %d\n",no,ffa());
    }
    return 0;
}
