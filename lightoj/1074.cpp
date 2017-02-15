#include<stdio.h>

#define N 201
#define M 19901
#define INF 100000000
#define CUBE(x) ((x)*(x)*(x))

struct Edge{
  int u,v,w;
};

Edge e[M];
int n,m,d[N],b[N],q;

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
      scanf("%d",&b[i]);
    scanf("%d",&m);
    for(int i=0;i<m;i++){
      scanf("%d%d",&e[i].u,&e[i].v);
      e[i].w=CUBE(b[e[i].v]-b[e[i].u]);
    }

    for(int u=1;u<=n;u++)
      d[u]=INF;
    d[1]=0;
    for(int i=1;i<=n-1;i++){
      for(int j=0;j<m;j++){
        int u=e[j].u,v=e[j].v,w=e[j].w;
        if(d[u]<INF&&d[v]>d[u]+w){
          d[v]=d[u]+w;
        }
      }
    }
    
    scanf("%d",&q);
    printf("Case %d:\n",++no);
    while(q--){
      int u;
      scanf("%d",&u);
      if(d[u]<3||d[u]>=INF)
        putchar('?');
      else
        printf("%d",d[u]);
      putchar('\n');
    }
  }
  return 0;
}
