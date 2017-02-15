#include <stdio.h>
#include <string.h>
#include <set>
using namespace std;

typedef pair<int,int> ii;

#define SZ 100005

bool vis[SZ];
int g[SZ],d[501][501],n,m,k,s[SZ];
set<int> T[SZ];
set<ii> G[SZ];

int dfs(int u,int grp){
  if(vis[u])return 0;
  vis[u]=true;
  int ans=(g[u]==grp);
  for(set<int>::iterator it=T[u].begin();it!=T[u].end();it++)
    ans+=dfs(*it,grp);
  return ans;
}

int main(){
  scanf("%d%d%d",&n,&m,&k);

  memset(d,0x3f,sizeof(d));
  for(int i=1;i<=k;i++){
    scanf("%d",&s[i]);
    s[i]+=s[i-1];    
    for(int u=s[i-1]+1;u<=s[i];u++)
      g[u]=i;
  }
  
  for(int i=1;i<=m;i++){
    int u,v,w;
    scanf("%d%d%d",&u,&v,&w);
    if(w==0){
      T[u].insert(v);
      T[v].insert(u);
    }else{
      G[u].insert(ii(v,w));
      G[v].insert(ii(u,w));
    }
  }

  
  
  for(int i=1;i<=k;i++){
    memset(vis,false,sizeof(vis));
    int tmp=dfs(s[i-1]+1,i);
    if(tmp!=s[i]-s[i-1]){
      puts("No");
      return 0;
    }
    d[i][i]=0;
  }

  for(int u=1;u<=n;u++){
    for(set<int>::iterator it=T[u].begin();it!=T[u].end();it++){
      int v=*it;
      if(g[u]!=g[v]){
        d[g[u]][g[v]]=0;
        d[g[v]][g[u]]=0;
      }
    }

    for(set<ii>::iterator it=G[u].begin();it!=G[u].end();it++){
      int v=it->first,w=it->second;
      if(g[u]!=g[v]){
        d[g[u]][g[v]]=min(d[g[u]][g[v]],w);
        d[g[v]][g[u]]=min(d[g[v]][g[u]],w);
      }
    }
  }

  for(int i=1;i<=k;i++)
    for(int u=1;u<=k;u++)
      for(int v=1;v<=k;v++)
        if(d[u][v]>d[u][i]+d[i][v])
          d[u][v]=d[u][i]+d[i][v];

  puts("Yes");
  for(int u=1;u<=k;u++){
    for(int v=1;v<=k;v++)
      if(d[u][v]==0x3f3f3f3f)
        printf("-1 ");
      else
        printf("%d ",d[u][v]);
    printf("\n");
  }
  
  return 0;
}
