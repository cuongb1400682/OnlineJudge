#include<stdio.h>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;

#define N 500
#define INF 0x3f3f3f3f

struct Edge{
    int u,v,c,f,i;
    Edge(int u=0,int v=0,int c=0,int i=-1):
        u(u),v(v),c(c),f(0),i(i){}
};

int n,m,s,t,nV,e[N],cnt[N],h[N],head[N],V[N];
bool active[N];
vector<Edge> edge;
queue<int> q;

void connect(int u,int v,int c){
    edge.push_back(Edge(u,v,c,head[u]));
    head[u]=edge.size()-1;
    edge.push_back(Edge(v,u,0,head[v]));
    head[v]=edge.size()-1;
}

void push_q(int u){
    if(u!=s&&u!=t&&!active[u]&&e[u]>0){
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
    int old_h=h[u];
    set_h(u,min_h+1);
    if(cnt[old_h]==0)
        gap(old_h);
}

void push(int i){
    if(h[edge[i].u]>h[edge[i].v])
        if(edge[i].c>edge[i].f&&e[edge[i].u]>0){
            int delta=min(edge[i].c-edge[i].f,e[edge[i].u]);
            edge[i].f+=delta;
            edge[i^1].f-=delta;
            e[edge[i].u]-=delta;
            e[edge[i].v]+=delta;
            push_q(edge[i].v);
        }
}

int preflow_push(){
    h[s]=n;
    cnt[n]=1;
    for(int i=head[s];i!=-1;i=edge[i].i){
        e[s]+=edge[i].c;
        push(i);
    }
    while(!q.empty()){
        int u=q.front();
        active[u]=false;
        q.pop();
        //printf("\npop u=%d\n",u);
        for(int i=head[u];e[u]>0&&i!=-1;i=edge[i].i){
            //printf("i=%d\n",i);
            push(i);
        }
        if(e[u]>0){
            //printf("old=%d\n",h[u]);
            lift(u);
            //printf("new=%d\n",h[u]);
            push_q(u);
        }
    }
    return e[t];
}

int main(){
    scanf("%d",&n);
    memset(V,-1,sizeof(V));
    memset(head,-1,sizeof(head));
    edge.clear();
    nV=0;
    for(int i=1;i<=n;i++){
        char a[4],b[4];
        int w;
        scanf("%s %s %d",a,b,&w);
        if(V[a[0]]==-1)V[a[0]]=++nV;
        if(V[b[0]]==-1)V[b[0]]=++nV;
        connect(V[a[0]],V[b[0]],w);
    }
    s=V['A'];
    t=V['Z'];
    printf("%d\n",preflow_push());
    return 0;
}
