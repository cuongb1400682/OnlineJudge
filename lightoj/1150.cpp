#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

#define N 50
#define INF 0x3f3f3f3f

const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};

typedef pair<int,int> ii;

int n,n_human,n_ghost,ghost[N][N],human[N][N],a[N][N],p[N*N];
char grid[N][N];
bool vis[N*N];

bool valid(int x,int y){
    return (x>=1)&&(y>=1)&&(x<=n)&&(y<=n)&&(grid[x][y]!='#');
}

void bfs(int s,int t){
    queue<ii> q;
    int d[N][N]={0},u,v,x,y;
    d[s][t]=1;
    q.push(ii(s,t));
    while(!q.empty()){
        u=q.front().first;
        v=q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            x=u+dx[i];
            y=v+dy[i];
            if(valid(x,y)&&d[x][y]==0){
                d[x][y]=d[u][v]+1;
                q.push(ii(x,y));
                if(grid[x][y]=='H'){
                    a[ghost[s][t]][human[x][y]]=d[x][y]*2;
                }
            }
        }
    }
}

void readf(){
    vector<ii> S;
    scanf("%d",&n);
    n_human=0;
    n_ghost=0;
    memset(human,0,sizeof(human));
    memset(ghost,0,sizeof(ghost));
    memset(a,-1,sizeof(a));
    for(int i=1;i<=n;i++){
        scanf("%s",grid[i]+1);
        for(int j=1;j<=n;j++)
            if(grid[i][j]=='H'){
                human[i][j]=++n_human;
            }else if(grid[i][j]=='G'){
                ghost[i][j]=++n_ghost;
                S.push_back(ii(i,j));
            }
    }
    for(int i=0;i<(int)S.size();i++){
        bfs(S[i].first,S[i].second);
    }
}

int dfs(int u,int limw){
    if(vis[u])return 0;
    vis[u]=true;
    for(int v=1;v<=n_human;v++){
        if(a[u][v]>=limw||a[u][v]==-1)continue;
        if(p[v]==-1||dfs(p[v],limw)){
            p[v]=u;
            return 1;
        }
    }
    return 0;
}

int weight(){
    int ans=-INF;
    for(int u=1;u<=n_human;u++)
        if(p[u]!=-1)
            ans=max(ans,a[p[u]][u]);
    return ans;
}

int hopcroft_karp(int w){
    int ans=0;
    memset(p,-1,sizeof(p));
    for(int u=1;u<=n_ghost;u++){
        memset(vis,0,sizeof(vis));
        ans+=dfs(u,w);
    }
    return ans;
}

void solve(){
    int mm=hopcroft_karp(INF);
    int ans=weight();    
    if(mm<n_human){
        puts("Vuter Dol Kupokat");
        return;
    }    
    int L=0,R=INF;
    while(L<=R){
        int M=(L+R)/2;
        if(hopcroft_karp(M)==mm){
            ans=weight();
            R=M-1;
        }else{
            L=M+1;
        }
    }
    printf("%d\n",ans);
}

int main(){
    int t,no=0;
    scanf("%d",&t);
    while(t--){
        readf();
        printf("Case %d: ",++no);
        solve();
    }
    return 0;
}
