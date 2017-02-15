#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;

typedef long long ll;

#define N 5005
#define INF 0x3f3f3f3f3f3f3f3fLL

struct Edge{
    ll u,v,c,f,i;
    Edge(ll u=0,ll v=0,ll c=0,ll i=-1):
        u(u),v(v),c(c),f(0),i(i){}
};

vector<Edge> edge;
ll head[N],n,m,e[N],h[N],cnt[N],max_rank;
bool active[N];
queue<ll> rank[N];

void connect(ll u,ll v,ll c){
    edge.push_back(Edge(u,v,c,head[u]));
    head[u]=edge.size()-1;
    edge.push_back(Edge(v,u,0,head[v]));
    head[v]=edge.size()-1;
}

void push_q(ll u){
    if(u!=1&&u!=n&&!active[u]){
        active[u]=true;
        rank[h[u]].push(u);
        if(max_rank<h[u])max_rank=h[u];
    }
}

void set_h(ll u,ll hh){
    cnt[h[u]]--;
    h[u]=hh;
    cnt[h[u]]++;
    push_q(u);
}

void gap(ll g){
    for(ll i=2;i<=n-1;i++)
        if(h[i]>g&&h[i]<=n)
            set_h(i,n+1);
}

void push(ll i){
    if(h[edge[i].u]>h[edge[i].v])
        if(e[edge[i].u]>0&&edge[i].c>edge[i].f){
            ll delta=min(e[edge[i].u],edge[i].c-edge[i].f);
            edge[i].f+=delta;
            edge[i^1].f-=delta;
            e[edge[i].u]-=delta;
            e[edge[i].v]+=delta;
            push_q(edge[i].v);
        }
}

void lift(ll u){
    if(u==1||u==n)
        return;
    ll min_h=INF;
    for(ll i=head[u];i!=-1;i=edge[i].i)
        if(edge[i].c>edge[i].f)
            min_h=min(min_h,h[edge[i].v]);
    if(min_h<INF){
        ll old_h=h[u];
        set_h(u,min_h+1);
        if(cnt[old_h]==0)
            gap(old_h);
    }
}

ll preflow_push(){
    h[1]=n;
    cnt[n]=1;
    for(ll i=head[1];i!=-1;i=edge[i].i){
        e[1]+=edge[i].c;
        push(i);
    }
    while(max_rank>=0){
        if(rank[max_rank].empty())
            max_rank--;
        else{
            int u=rank[max_rank].front();
            rank[max_rank].pop();
            active[u]=false;
            for(int i=head[u];e[u]>0&&i!=-1;i=edge[i].i)
                push(i);
            if(e[u]>0)
                lift(u);
        }
    }
    return e[n];
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=m;i++){
        ll u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        connect(u,v,w);
        connect(v,u,w);
    }
    printf("%lld\n",preflow_push());
    return 0;
}
