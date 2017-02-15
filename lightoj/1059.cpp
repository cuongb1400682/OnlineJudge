#include<stdio.h>
#include<algorithm>
using namespace std;

#define N 10005
#define M 100005

struct Edge{
  int u,v,w;
}e[M];

int p[N],n,m,cost,n_cmp,ans,sum,cmp;

bool operator<(Edge a,Edge b){
  return a.w<b.w;
}

int root_of(int u){
  return p[u]==u?u:p[u]=root_of(p[u]);
}

bool join(int u,int v){
  int r=root_of(u),s=root_of(v);
  if(r==s)return false;
  p[r]=s;
  n_cmp--;
  return true;
}

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d%d%d",&n,&m,&cost);
    for(int i=0;i<m;i++)
      scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    for(int u=1;u<=n;u++)
      p[u]=u;
    sort(e,e+m);
    ans=n*cost;
    cmp=n;
    sum=0;    
    n_cmp=n;
    for(int i=0;i<m;i++)
      if(join(e[i].u,e[i].v)){
        sum+=e[i].w;
        if(ans>sum+n_cmp*cost)
          ans=sum+n_cmp*cost,cmp=n_cmp;
      }        
    printf("Case %d: %d %d\n",++no,ans,cmp);
  }
  return 0;
}
