#include <stdio.h>
#include <math.h>
#include <string.h>
#include <queue>
using namespace std;

#define N 250
#define M 50000
#define INF 0x3f3f3f3f

struct Edge{
    int u,v,c,i;
    Edge(int _u=0,int _v=0,int _c=0,int _i=-1):
        u(_u),v(_v),c(_c),i(_i){}
};

Edge edge[M];
int head[N],n,x[N],y[N],peng[N],jump[N],n_edge,s,t,h[N],cnt[N],e[N],flow[M];
bool active[N];
queue<int> q;
float dist;

void connect(int u,int v,int c){
    edge[n_edge++]=Edge(u,v,c,head[u]);
    head[u]=n_edge-1;
    edge[n_edge++]=Edge(v,u,0,head[v]);
    head[v]=n_edge-1;
}

void push_queue(int u){
    if(!active[u]&&u!=s&&u!=t){
        q.push(u);
        active[u]=true;
    }
}

void gap(int g){
    for(int i=1;i<=n;i++)
        if(h[i]>g&&h[i]<=n&&i!=t){
            cnt[h[i]]--;
            h[i]=n+1;
            cnt[h[i]]++;
        }
}

void push(int i){
    if(h[edge[i].u]>h[edge[i].v]&&e[edge[i].u]>0)
        if(edge[i].c>flow[i]){
            int delta=min(e[edge[i].u],edge[i].c-flow[i]);
            flow[i]+=delta;
            flow[i^1]-=delta;
            e[edge[i].u]-=delta;
            e[edge[i].v]+=delta;
            push_queue(edge[i].v);
        }
}

void lift(int u){
    if(u!=s&&u!=t){
        int min_h=INF;
        for(int i=head[u];i!=-1;i=edge[i].i)
            if(edge[i].c>flow[i])
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

int preflow_push(){
    memset(e,0,sizeof(e));
    memset(h,0,sizeof(h));
    memset(active,0,sizeof(active));
    memset(cnt,0,sizeof(cnt));
    memset(flow,0,sizeof(flow));
    q=queue<int>();
    h[s]=n;
    for(int i=head[s];i!=-1;i=edge[i].i){
        e[s]+=edge[i].c;
        push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        active[u]=false;
        for(int i=head[u];i!=-1&&e[u]>0;i=edge[i].i)
            push(i);
        if(e[u]>0){
            lift(u);
            push_queue(u);
        }
    }
    return e[t];
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d%f",&n,&dist);
        n_edge=0;
        memset(head,-1,sizeof(head));
        s=1;
        int total_peng=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d%d%d",&x[i],&y[i],&peng[i],&jump[i]);
            connect(2*i,2*i+1,jump[i]);
            connect(s,2*i,peng[i]);
            total_peng+=peng[i];
        }
        for(int i=1;i<=n-1;i++)
            for(int j=i+1;j<=n;j++)
                if(hypot(x[i]-x[j],y[i]-y[j])<=dist){
                    connect(2*i+1,2*j,INF);
                    connect(2*j+1,2*i,INF);
                }
        vector<int> ans;
        for(int i=1;i<=n;i++){
            t=2*i;
            if(preflow_push()>=total_peng)
                ans.push_back(i-1);
        }
        printf("Case %d:",no);
        if(ans.empty())
            puts(" -1");
        else{
            for(int i=0;i<(int)ans.size();i++)
                printf(" %d",ans[i]);
            putchar('\n');
        }
    }
    return 0;
}
