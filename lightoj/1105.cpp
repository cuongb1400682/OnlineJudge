#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<string>
using namespace std;

typedef long long ll;

const int cumsum[]={
    1,2,4,7,12,20,33,54,88,143,232,376,609,986,1596,
    2583,4180,6764,10945,17710,28656,46367,75024,121392,
    196417,317810,514228,832039,1346268,2178308,3524577,
    5702886,9227464,14930351,24157816,39088168,63245985,
    102334154,165580140,267914295,433494436,701408732,1134903169
};

class Solver{
    int dp[100][2],height;
    string solve(int h,char c,int n){
        string ans;
        ans.push_back(c);
        if(h==0)
            return ans;
        for(int i=0;i<=(c=='0');i++){
            if(n>dp[h-1][i]){
                n-=dp[h-1][i];
            }else{
                ans+=solve(h-1,i+'0',n);
                break;
            }
        }
        return ans;
    }

public:
    string solve(int n){        
        const int *p=lower_bound(cumsum,cumsum+43,n);
        n=n-p[-1];
        height=p-cumsum;
        memset(dp,0,sizeof(dp));
        dp[0][0]=dp[0][1]=1;
        for(int i=1;i<=height;i++){
            dp[i][0]=dp[i-1][0]+dp[i-1][1];
            dp[i][1]=dp[i-1][0];
        }
        return solve(height,'1',n);
    }
};

int main(){
    int n_case,n;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d",&n);
        printf("Case %d: %s\n",no,Solver().solve(n).c_str());
    }
    return 0;
}
