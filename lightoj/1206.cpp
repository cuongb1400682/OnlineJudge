#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
using namespace std;

typedef pair<int,int> ii;

#define N 512

struct Ride{
    int tm,a,b,c,d;
};

Ride a[N];
bool vis[N];
int n,p[N];
vector<int> G[N];

int dist(ii a,ii b){
	return abs(a.first-b.first)+abs(a.second-b.second);
}

bool is_adj(Ride x,Ride y){
	int d2=y.tm-x.tm;
	int d1=dist(ii(x.a,x.b),ii(x.c,x.d))+
		dist(ii(x.c,x.d),ii(y.a,y.b));
	return d2>d1;
}

int dfs(int u){
    if(vis[u])return 0;
    vis[u]=true;
    for(int i=0;i<(int)G[u].size();i++){
        if(p[G[u][i]]==-1||dfs(p[G[u][i]])){
            p[G[u][i]]=u;
            return 1;
        }
    }
    return 0;
}

int main(){
    int nTest,no=0;
    scanf("%d",&nTest);
    while(nTest--){
        scanf("%d",&n);
		for(int i=1;i<=n;i++)
			G[i].clear();

		int lim=0;
		for(int i=1;i<=n;i++){
			int hh,mm;
			scanf("%d:%d%d%d%d%d",
				  &hh,&mm,
				  &a[i].a,&a[i].b,
				  &a[i].c,&a[i].d);
			a[i].tm=hh*60+mm;
		}
        for(int i=1;i<=n-1;i++)
			for(int j=i+1;j<=n;j++)
				if(is_adj(a[i],a[j])){
					G[i].push_back(j);
					//printf("added %d %d\n",i,j);
				}
        int ans=0;
        memset(p,-1,sizeof(p));
        for(int u=1;u<=n;u++){
            memset(vis,0,sizeof(vis));
            ans+=dfs(u);
        }
        printf("Case %d: %d\n",++no,n-ans);
    }
    return 0;
}
