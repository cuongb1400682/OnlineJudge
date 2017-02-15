#include<stdio.h>
#include<string.h>

#define MOD 100000007
#define N 10005

int f[200][N],n,K,a[200];

int main(){
    int n_test;
    scanf("%d",&n_test);
    for(int no=1;no<=n_test;no++){
        scanf("%d%d",&n,&K);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        memset(f,0,sizeof(f));
        for(int i=0;i<=n;i++)
            f[i][0]=1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=K;j++)
                f[i][j]=f[i-1][j]+(j>=a[i]?f[i][j-a[i]]:0);
        printf("Case %d: %d\n",no,f[n][K]);
    }
    return 0;
}

