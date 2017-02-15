#include<stdio.h>
#include<string.h>

typedef long long ll;

#define MOD 100000007
#define N 100

int a[N],c[N],n,K;
ll f[N][1001];

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d%d",&n,&K);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&c[i]);
        memset(f,0,sizeof(f));
        f[0][0]=1;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=K;j++){
                if(f[i][j]==0)continue;
                for(int x=0;x<=c[i+1];x++){
                    if(j+x*a[i+1]>K)break;
                    (f[i+1][j+x*a[i+1]]+=f[i][j])%=MOD;
                }
            }
        }
        printf("Case %d: %lld\n",no,f[n][K]);
    }
    return 0;
}
