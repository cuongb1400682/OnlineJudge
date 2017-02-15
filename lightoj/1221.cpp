#include<stdio.h>
#include<string.h>
#define N 101
#define M 9901

struct Edge {int u,v,w;} e[M];
int n,m,p,d[N];

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d%d%d",&n,&m,&p);
    for(int i=0;i<m;i++){
      int icm,exp;
      scanf("%d%d%d%d",&e[i].u,&e[i].v,&icm,&exp);
      e[i].w=-(icm-p*exp);
    }

    memset(d,0x3f,sizeof(d));
    d[0]=0;

    for(int i=1;i<=n-1;i++){
      for(int j=0;j<m;j++){
        int u=e[j].u,v=e[j].v,w=e[j].w;
        if(d[v]>d[u]+w)
          d[v]=d[u]+w;
      }
    }

    bool neg=false;
    for(int j=0;j<m;j++){
      int u=e[j].u,v=e[j].v,w=e[j].w;
      if(d[v]>d[u]+w){
        neg=true;
        break;
      }
    }

    printf("Case %d: %s\n",++no,neg?"YES":"NO");
  }
  return 0;
}
