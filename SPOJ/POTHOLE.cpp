#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

#define N 1000
#define INF 0x3f3f3f3f

struct Edge{
    int u,v,c,f,i;
    Edge(int u=0,int v=0,int c=0,int i=-1):
        u(u),v(v),c(c),f(0),i(i){}
};

vector<Edge> edge;
int head[N],e[N],cnt[N],h[N],s,t,n;
queue<int> q;
bool active[N];

void connect(int u,int v,int c){
    edge.push_back(Edge(u,v,c,head[u]));
    head[u]=edge.size()-1;
    edge.push_back(Edge(v,u,0,head[v]));
    head[v]=edge.size()-1;
}

void push_q(int u){
    if(u!=s&&u!=t&&!active[u]){
        active[u]=true;
        q.push(u);
    }
}

void set_h(int u,int hh){
    cnt[h[u]]--;
    h[u]=hh;
    cnt[h[u]]++;
}

void gap(int g){
    for(int u=1;u<=n;u++)
        if(u!=s&&u!=t&&h[u]>g&&h[u]<=n)
            set_h(u,n+1);
}

void lift(int u){
    if(u==t||u==s)return;
    int min_h=INF;
    for(int i=head[u];i!=-1;i=edge[i].i)
        if(edge[i].c>edge[i].f)
            min_h=min(min_h,h[edge[i].v]);
    if(min_h<INF){
        int old_h=h[u];
        set_h(u,min_h+1);
        if(cnt[old_h]==0)
            gap(old_h);
    }
}

void push(int i){
    if(h[edge[i].u]>h[edge[i].v])
        if(edge[i].c>edge[i].f&&e[edge[i].u]>0){
            int delta=min(e[edge[i].u],edge[i].c-edge[i].f);
            edge[i].f+=delta;
            edge[i^1].f-=delta;
            e[edge[i].u]-=delta;
            e[edge[i].v]+=delta;
            push_q(edge[i].v);
        }
}

int preflow_push(){
    memset(h,0,sizeof(h));
    memset(e,0,sizeof(e));
    memset(cnt,0,sizeof(cnt));
    memset(active,0,sizeof(active));
    q=queue<int>();
    h[s]=n;
    cnt[n]=1;
    for(int i=head[s];i!=-1;i=edge[i].i){
        e[s]+=edge[i].c;
        push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        active[u]=false;
        for(int i=head[u];e[u]>0&&i!=-1;i=edge[i].i)
            push(i);
        if(e[u]>0){
            lift(u);
            push_q(u);
        }
    }
    return e[t];
}

void readf(){
    edge.clear();
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++){
        int u,k;
        scanf("%d",&k);
        while(k--){
            scanf("%d",&u);
            connect(i,u,(u==1||u==n||i==1||i==n)?1:INF);
        }
    }
    s=1;
    t=n;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        readf();
        printf("%d\n",preflow_push());
    }
    return 0;
}
