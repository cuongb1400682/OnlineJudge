#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int,int> ii;
typedef long long ll;

#define N 32

char str1[N],str2[N];
int len1,len2;
ll dp1[N][N],dp2[N][N];

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%s %s",str1+1,str2+1);
        len1=strlen(str1+1);
        len2=strlen(str2+1);
        memset(dp1,0,sizeof(dp1));
        memset(dp2,0,sizeof(dp2));
        for(int i=0;i<=len1;i++){
            dp1[i][0]=i;
            dp2[i][0]=1;
        }
        for(int i=0;i<=len2;i++){
            dp1[0][i]=i;
            dp2[0][i]=1;
        }
        for(int i=1;i<=len1;i++)
            for(int j=1;j<=len2;j++)
                if(str1[i]==str2[j]){
                    dp1[i][j]=dp1[i-1][j-1]+1;
                    dp2[i][j]=dp2[i-1][j-1];
                }else{
                    dp1[i][j]=min(dp1[i-1][j],dp1[i][j-1])+1;
                    if(dp1[i-1][j]==dp1[i][j-1])
                        dp2[i][j]=dp2[i-1][j]+dp2[i][j-1];
                    else if(dp1[i-1][j]<dp1[i][j-1])
                        dp2[i][j]=dp2[i-1][j];
                    else
                        dp2[i][j]=dp2[i][j-1];
                }
        printf("Case %d: %lld %lld\n",no,dp1[len1][len2],dp2[len1][len2]);
    }
    return 0;
}
