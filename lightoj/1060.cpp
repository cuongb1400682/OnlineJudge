#include<stdio.h>
#include<string.h>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

#define N 20

typedef long long ll;

string s;
ll dp[1<<N],n;

string solve(int st,int n){
    if(st==0)return "";
    string ans;
    vector<int> P;
    int vis=0;
    for(int i=0;i<s.size();i++)
        if(((st>>i)&1)&&!((vis>>(s[i]-'a'))&1)){
            P.push_back(i);
            vis|=1<<(s[i]-'a');
        }
    for(int i=0;i<P.size();i++){
        int j=P[i];
        if(n>dp[st-(1<<j)])
            n-=dp[st-(1<<j)];
        else{
            ans.push_back(s[j]);
            ans+=solve(st-(1<<j),n);
            break;
        }
    }
    return ans;
}

ll calcdp(int st){
    if(st==0)return dp[st]=1;
    if(dp[st]!=-1)return dp[st];
    int vis=0;
    ll ans=0;
    for(int i=0;i<s.size();i++)
        if(((st>>i)&1)&&!((vis>>(s[i]-'a'))&1)){
            ans+=calcdp(st-(1<<i));
            vis|=1<<(s[i]-'a');
        }
    return dp[st]=ans;
}

int main(){
    int n_test;
    scanf("%d",&n_test);
    char buf[50];
    for(int no=1;no<=n_test;no++){
        scanf("%s %lld",buf,&n);
        s=string(buf);
        sort(s.begin(),s.end());
        memset(dp,-1,sizeof(dp));
        if(n>calcdp((1<<s.size())-1)){
            printf("Case %d: Impossible\n",no);
        }else
            printf("Case %d: %s\n",no,solve((1<<s.size())-1,n).c_str());
    }
    return 0;
}
