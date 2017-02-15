#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

#define N 20005
#define INF 0x3f3f3f3f

struct Edge{
    int u,v,c,nxt,f;
    Edge(int _u=0,int _v=0,int _c=0,int _nxt=-1):
        u(_u),v(_v),c(_c),nxt(_nxt),f(0){}
};

int head[N],n_edge,h[N],e[N],cnt[2*N],n,m,s,t;
vector<Edge> edge;
queue<int> q;

void connect(int u,int v,int w){
    edge.push_back(Edge(u,v,w,head[u]));
    head[u]=edge.size()-1;
    edge.push_back(Edge(v,u,0,head[v]));
    head[v]=edge.size()-1;
}

void readf(){
    int u,v,w;
    memset(head,-1,sizeof(head));
    edge.clear();
    scanf("%d%d",&n,&m);
    s=0;
    t=n+1;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&u,&v);
        connect(s,i,u);
        connect(i,t,v);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        connect(u,v,w);
        connect(v,u,w);
    }
}

void gap(int g){
    for(int i=1;i<=n;i++){
        if(i!=s&&h[i]>g&&h[i]<=n){
            cnt[h[i]]--;
            h[i]=n+1;
            cnt[n+1]++;
        }
    }
}

void push(int i){
    if(e[edge[i].u]<=0||h[edge[i].u]<=h[edge[i].v]||edge[i].c<=edge[i].f)
        return;
    int delta=min(e[edge[i].u],edge[i].c-edge[i].f);
    edge[i].f+=delta;
    edge[i^1].f-=delta;
    e[edge[i].u]-=delta;
    e[edge[i].v]+=delta;
    if(e[edge[i].v]>0&&edge[i].v!=s&&edge[i].v!=t)
        q.push(edge[i].v);
}

void lift(int u){
    if(u!=s&&u!=t&&e[u]>0){
        int min_h=INF;
        for(int i=head[u];i!=-1;i=edge[i].nxt)
            if(edge[i].c>edge[i].f)
                min_h=min(min_h,h[edge[i].v]);
        if(min_h<INF){
            cnt[h[u]]--;
            if(cnt[h[u]]==0)
                gap(h[u]);
            h[u]=min_h+1;
            cnt[h[u]]++;            
        }
    }
}

void preflow_push(){
    memset(e,0,sizeof(e));
    memset(h,0,sizeof(h));
    memset(cnt,0,sizeof(cnt));
    h[s]=n;
    for(int i=head[s];i!=-1;i=edge[i].nxt){
        e[edge[i].u]+=edge[i].c;
        push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i!=-1&&e[u]>0;i=edge[i].nxt)
            push(i);
        if(e[u]>0){
            lift(u);
            q.push(u);
        }
    }
}

int main(){
    readf();
    preflow_push();
    printf("%d\n",e[t]);
    return 0;
}
