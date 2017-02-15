#include<stdio.h>
#include<algorithm>
using namespace std;

#define N 105
#define INF 1000000000

struct Edge{
  int u,v,w;
}e[2*N*N];

int p[N],n,m;

int root_of(int u){
  return u==p[u]?u:p[u]=root_of(p[u]);
}

bool join(int u,int v){
  int s=root_of(u),r=root_of(v);
  if(s==r)return false;
  p[s]=r;
  return true;
}

bool cmp_asc(Edge a,Edge b){
  return a.w<b.w;
}

bool cmp_dec(Edge a,Edge b){
  return a.w>b.w;
}

int kruskal(bool asc){
  int ans=0;
  for(int u=0;u<n;u++)
    p[u]=u;
  sort(e,e+m,asc?cmp_asc:cmp_dec);
  for(int i=0;i<m;i++)
    if(join(e[i].u,e[i].v))
      ans+=e[i].w;
  return ans;
}

void readf(){
  int amin[N][N],amax[N][N];
  scanf("%d",&n);
  n++;
  for(int u=0;u<n;u++)
    for(int v=0;v<n;v++)
      amin[u][v]=INF,amax[u][v]=-INF;
  while(true){
    int u,v,w;
    scanf("%d%d%d",&u,&v,&w);
    if(!(u||v||w))break;
    amin[u][v]=min(amin[u][v],w);
    amax[u][v]=max(amax[u][v],w);
  }
  m=0;
  for(int u=0;u<n;u++)
    for(int v=0;v<n;v++){
      if(amin[u][v]!=INF){
        e[m].u=u;
        e[m].v=v;
        e[m].w=amin[u][v];
        m++;
      }
      if(amax[u][v]!=-INF){
        e[m].u=u;
        e[m].v=v;
        e[m].w=amax[u][v];
        m++;
      }
    }
}

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    readf();
    int ans=kruskal(1)+kruskal(0);
    printf("Case %d: ",++no);
    if(ans&1)
      printf("%d/2\n",ans);
    else
      printf("%d\n",ans>>1);
  }
  return 0;
}
