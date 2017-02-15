#include<stdio.h>
#include<algorithm>
using namespace std;

#define N 64

struct Edge{
  int u,v,w;
  Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
};

Edge e[N*N];
int n,m,p[N],ans;

bool operator<(Edge a,Edge b){
  return a.w<b.w;
}

int root_of(int u){
  return p[u]<0?u:p[u]=root_of(p[u]);
}

bool join(int u,int v){
  int r=root_of(u),s=root_of(v);
  if(r==s)return false;
  if(p[r]<p[s]){
    p[s]=r;
    p[r]--;
  }else{
    p[r]=s;
    p[s]--;
  }
  return true;
}

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d",&n);
    ans=0;
    m=0;
    for(int u=1;u<=n;u++)
      for(int v=1;v<=n;v++){
        int w;
        scanf("%d",&w);
        if(w!=0)
          e[m++]=Edge(u,v,w);
        ans+=w;
      }
    sort(e,e+m);
    for(int u=1;u<=n;u++)
      p[u]=-1;
    int n_edge=0;
    for(int i=0;i<m;i++){
      if(join(e[i].u,e[i].v)){
        ans-=e[i].w;
        n_edge++;
      }
    }
    printf("Case %d: %d\n",++no,n_edge==n-1?ans:-1);
  }
  return 0;
}
