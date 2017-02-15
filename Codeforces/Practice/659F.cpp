#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> ii;

#define SZ 1001

const ll dx[]={0,1,0,-1};
const ll dy[]={1,0,-1,0};

vector<ii> cell,S;
ll a[SZ][SZ],n,m,ans[SZ][SZ],k;
bool vis[SZ][SZ];

bool valid(ll x,ll y){
  return x>0&&y>0&&x<=n&&y<=m;
}

bool cmp(ii x,ii y){
  return a[x.first][x.second]<a[y.first][y.second];
}

void dfs(ll x,ll y,vector<ii> &S,ll value){
  if(vis[x][y])return;
  vis[x][y]=true;
  S.push_back(ii(x,y));
  if(S.size()>=k/value)
    return;
  for(ll i=0;i<4;i++){
    ll u=x+dx[i],v=y+dy[i];
    if(valid(u,v)&&a[u][v]>=value){
      dfs(u,v,S,value);
      if(S.size()>=k/value)
        return;
    }
  }
}

void print(ll value,const vector<ii> &S){
  memset(ans,0,sizeof(ans));
  for(ll i=0;i<k/value;i++){
    ll x=S[i].first,y=S[i].second;
    ans[x][y]=value;
  }
  puts("YES");
  for(ll u=1;u<=n;u++){
    for(ll v=1;v<=m;v++)
      cout<<ans[u][v]<<' ';
    cout<<'\n';
  }
}

int main(){
  cin>>n>>m>>k;
  for(ll i=1;i<=n;i++)
    for(ll j=1;j<=m;j++){
      cin>>a[i][j];
      if(k%a[i][j]==0&&k/a[i][j]<=n*m)
        cell.push_back(ii(i,j));
    }
  sort(cell.begin(),cell.end(),cmp);
    
  for(ll i=0,j;i<(ll)cell.size();i=j){
    ll value=a[cell[i].first][cell[i].second];
    memset(vis,false,sizeof(vis));
    for(j=i;j<(ll)cell.size();j++){
      ll x=cell[j].first,y=cell[j].second;
      if(a[x][y]!=value)
        break;

      if(!vis[x][y]){
        S.clear();
        dfs(x,y,S,value);
        
        if(S.size()>=k/value){
          print(value,S);
          return 0;
        }
      }
    }
  }
  puts("NO");
  return 0;
}

