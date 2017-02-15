#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

#define N 16
#define K 20

typedef pair<int,int> ii;
typedef long long ll;

ll dp[1<<N][K];
int n,k;
char perm[K];

int todigit(char c){
    if(c>='0'&&c<='9')
        return c-'0';
    else
        return c-'A'+10;
}

bool cmp(int a,int b){
    return __builtin_popcount(a)<__builtin_popcount(b);
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d%d",&n,&k);
        scanf("%s",perm);

        int st=0;

        memset(dp,0,sizeof(dp));
        int n_perm=strlen(perm);
        for(int i=0;i<n_perm;i++){
            int c=todigit(perm[i]);
            dp[1<<c][c%k]+=1;
            st|=(1<<c);
        }            

        vector<int> states;
        for(int i=0;i<(1<<n);i++)
            states.push_back(i);
        sort(states.begin(),states.end(),cmp);
        
        for(int i=0;i<(int)states.size();i++){
            int state=states[i];
            for(int j=0;j<k;j++){
                if(dp[state][j]==0)continue;
                for(int h=0;h<n_perm;h++){
                    int c=todigit(perm[h]);
                    if((state>>c)&1)continue;
                    dp[state|(1<<c)][(j*n+c)%k]+=dp[state][j];
                }
            }
        }
        
        printf("Case %d: %lld\n",no,dp[st][0]);
    }
    return 0;
}
