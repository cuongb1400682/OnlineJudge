#include<stdio.h>
#include<string.h>
#include<string>
using namespace std;

#define N 25
#define INF 1000000000

int n,x[N],y[N],d[N][N],dp[1<<N],nxt[1<<N];

int bit(int x){
  int ans=0;
  while(!(x&1))
    x>>=1,ans++;
  return ans;
}

int solve(int st){
  if(dp[st]!=-1)return dp[st];
  if(st==0)return 0;
  int u=bit(st&(-st));
  st-=st&(-st);
  int ans=solve(st)+d[0][u+1]*2,pp=st,tmp;
  for(int v=0;v<n;v++)
    if((st>>v)&1){
      tmp=solve(st-(1<<v))+d[0][u+1]+d[u+1][v+1]+d[v+1][0];
      if(ans>tmp){
        ans=tmp;
        pp=st-(1<<v);
      }
    }
  st|=(1<<u);
  nxt[st]=pp;
  return dp[st]=ans;
}

int main(){
  scanf("%d%d",&x[0],&y[0]);
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
    scanf("%d%d",&x[i],&y[i]);
  n++;
  for(int i=0;i<n-1;i++)
    for(int j=i+1;j<n;j++)
      d[j][i]=d[i][j]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
  memset(dp,-1,sizeof(dp));
  memset(nxt,-1,sizeof(nxt));
  printf("%d\n",solve((1<<(n-1))-1));
  int prev=(1<<(n-1))-1;
  for(int st=nxt[(1<<(n-1))-1];st!=-1;st=nxt[st]){
    printf("0 ");
    for(prev^=st;prev;prev-=prev&(-prev))
      printf("%d ",bit(prev&(-prev))+1);
    prev=st;
  }
  printf("0\n");
  return 0;
}
