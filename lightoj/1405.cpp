#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>
using namespace std;

#define N 20100
#define M 100100
#define INF 0x3f3f3f3f

const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

struct Edge{
    int u,v,c,nxt;
    Edge(int u=0,int v=0,int c=0,int nxt=-1):
        u(u),v(v),c(c),nxt(nxt){}
};

Edge edge[M];
int head[N],s,t,m,n,nStar,nEdge;
char grid[1005][1005];

void connect(int u,int v,int w){
    edge[nEdge++]=Edge(u,v,w,head[u]);
    head[u]=nEdge-1;
    edge[nEdge++]=Edge(v,u,0,head[v]);
    head[v]=nEdge-1;
}

int ffa(){
    int p[N],f[N],ans=0;
    while(1){
        queue<int> q;
        q.push(s);
        memset(f,0x3f,sizeof(f));
        memset(p,-1,sizeof(p));
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=head[u];i!=-1;i=edge[i].nxt){
                Edge e=edge[i];
                if(e.v!=s&&p[e.v]==-1&&e.c>0){
                    p[e.v]=i;
                    f[e.v]=min(f[u],e.c);
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
            int j=i^1;
            edge[i].c-=f[t];
            edge[j].c+=f[t];
        }
        ans+=f[t];
    }
    return ans;
}

bool valid(int x,int y){
    return (x>=1)&&(y>=1)&&(x<=m)&&(y<=n);
}

int ver(int i,int j){
    return n*(i-1)+j;
}

void readf(){
    nEdge=0;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++){
        scanf("%s",grid[i]+1);
        for(int j=1;j<=n;j++){
            int u=ver(i,j);
            connect(2*u,2*u+1,1);
        }
    }
    s=1;
    t=2*ver(m,n)+2;
    nStar=0;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++){
            int u=ver(i,j);
            if(grid[i][j]=='*'){
                connect(s,2*u,1),nStar++;
            }
            if(i==1||j==1||i==m||j==n)
                connect(2*u+1,t,1);
            for(int h=0;h<4;h++){
                int x=i+dx[h];
                int y=j+dy[h];
                if(valid(x,y)&&grid[x][y]!='*'){
                    int v=ver(x,y);
                    connect(2*u+1,2*v,1);
                }
            }
        }
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        readf();
        printf("Case %d: %s\n",no,ffa()==nStar?"yes":"no");
    }
    return 0;
}

