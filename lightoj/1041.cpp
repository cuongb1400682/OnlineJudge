#include<stdio.h>
#include<algorithm>
#include<map>
#include<vector>
#include<string>
using namespace std;

#define N 200

struct Edge{
  int u,v,w;
}e[N];

int p[N],n,m,ans,cnt;

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
  return true;
}

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    scanf("%d",&n);
    map<string,int> h;
    char city0[N],city1[N];
    int weight;
    m=0;
    for(int i=0;i<n;i++){
      scanf("%s%s%d",city0,city1,&weight);
      if(h.count(city0)==0)
        h[city0]=h.size()-1;
      if(h.count(city1)==0)
        h[city1]=h.size()-1;
      e[m].u=h[city0];
      e[m].v=h[city1];
      e[m].w=weight;
      m++;
    }
    n=h.size();
    for(int u=0;u<n;u++)
      p[u]=u;
    sort(e,e+m);
    ans=0;
    cnt=0;
    for(int i=0;i<m;i++)
      if(join(e[i].u,e[i].v)){
        ans+=e[i].w;
        cnt++;
      }
    if(cnt==n-1)
      printf("Case %d: %d\n",++no,ans);
    else
      printf("Case %d: Impossible\n",++no);
  }
  return 0;
}
