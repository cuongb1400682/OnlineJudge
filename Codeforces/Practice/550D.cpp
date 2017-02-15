#include <stdio.h>
#include <vector>

using namespace std;

typedef pair<int,int> ii;

int k,label;
vector<ii> edge;

inline void add_edge(int u,int v){
  edge.push_back(ii(u,v));
}

ii gen_kn(int &label,int n){
  ii ans=ii(label,label+1);
  for(int u=label;u<=label+n-2;u++)
    for(int v=u+1;v<=label+n-1;v++)
      if (ii(u,v)!=ans){
        add_edge(u,v);
      }
  label+=n;
  return ans;
}

void solve(int n){
  label=1;
  vector<ii> inlet;
  for(int i=1;i<=n-1;i++){
    inlet.push_back(gen_kn(label,n+1));
  }
  int u=label,v=label+1;
  add_edge(u,v);
  for(int i=0;i<(n-1)/2;i++){
    add_edge(v,inlet[i].first);
    add_edge(v,inlet[i].second);
  }
  for(int i=(n-1)/2;i<n-1;i++){
    add_edge(u,inlet[i].first);
    add_edge(u,inlet[i].second);    
  }
}

void print(){
  puts("YES");
  printf("%d %d\n",label+1,(int)edge.size());
  for(int i=0;i<(int)edge.size();i++)
    printf("%d %d\n",edge[i].first,edge[i].second);
}

int main(){
  scanf("%d",&k);
  if(k&1){
    solve(k);
    print();
  }else{
    puts("NO");
  }
  return 0;
}
