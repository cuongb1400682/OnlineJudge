#include<stdio.h>
#include<string.h>

#define INF 1000000000

int f[32][3],n;

int min(int a,int b){
    return a>b?b:a;
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d",&n);
        memset(f[0],0,sizeof(f[0]));
        for(int i=1;i<=n;i++){
            for(int j=0;j<3;j++){
                scanf("%d",&f[i][j]);
                int ans=INF;
                for(int k=0;k<3;k++)
                    if(k!=j)
                        ans=min(ans,f[i][j]+f[i-1][k]);
                f[i][j]=ans;
            }
        }
        printf("Case %d: %d\n",no,min(min(f[n][0],f[n][1]),f[n][2]));
    }
    return 0;
}
