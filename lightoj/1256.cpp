#include<stdio.h>
#include<string.h>
#include<vector>
#include<stdlib.h>
#include<list>
using namespace std;

#define N 50
#define M 1024

struct Edge{
  char str[N];
  int v;
  bool usable;
  Edge(const char*s="",int v=0){
    this->v=v;
    strcpy(str,s);
    usable=true;
  }
};

int n,in[N],out[N];
Edge e[M];
vector<int> G[N];
bool vis[N];
list<int> ans;

void readf(){
  char word[N];
  int lab[N],n_lab;
  memset(lab,-1,sizeof(lab));
  memset(in,0,sizeof(in));
  memset(out,0,sizeof(out));
  n_lab=0;
  scanf("%d",&n);
  for(int u=0;u<N;u++)
    G[u].clear();
  for(int i=1;i<=n;i++){
    scanf("%s",word);
    int u=word[0]-'a';
    int v=word[strlen(word)-1]-'a';
    if(lab[u]==-1)lab[u]=++n_lab;
    if(lab[v]==-1)lab[v]=++n_lab;
    u=lab[u];
    v=lab[v];
    e[i]=Edge(word,v);
    G[u].push_back(i);
    in[v]++;
    out[u]++;
  }
  n=n_lab;
}

void dfs(int u){
  if(vis[u])return;
  vis[u]=true;
  for(int i=0;i<(int)G[u].size();i++)
    dfs(e[G[u][i]].v);
}

int find_src(){
  int ans=-1,cnt=0;
  memset(vis,0,sizeof(vis));
  for(int u=1;u<=n;u++){
    int diff=out[u]-in[u];
    if(abs(diff)>1)
      return -1;
    if(diff==1)
      ans=u;
    if(diff==0)
      cnt++;
  }
  if(cnt!=n&&cnt!=n-2)
    return -1;
  if(ans==-1)
    ans=1;
  dfs(ans);
  for(int u=1;u<=n;u++)
    if(!vis[u])
      return -1;
  return ans;
}

void find_circle(int u,list<int>::iterator it){
  for(int i=0;i<(int)G[u].size();i++){
    if(e[G[u][i]].usable){
      e[G[u][i]].usable=false;
      find_circle(e[G[u][i]].v,ans.insert(it,G[u][i]));
    }
  }
}

int main(){
  int nTest,no=0;
  scanf("%d",&nTest);
  while(nTest--){
    printf("Case %d: ",++no);
    readf();
    int src=find_src();
    if(src!=-1){
      puts("Yes");
      ans.clear();
      find_circle(src,ans.begin());
      printf("%s",e[*ans.rbegin()].str);
      for(list<int>::reverse_iterator it=++ans.rbegin();it!=ans.rend();it++)
        printf(" %s",e[*it].str);
      printf("\n");
    }else{
      puts("No");
    }
  }
  return 0;
}
