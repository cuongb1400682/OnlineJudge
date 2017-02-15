#include<stdio.h>
#include<string.h>

char s[64];
int n;
long long f[64][64];

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%s",s+1);
        n=strlen(s+1);
        memset(f,0,sizeof(f));
        for(int i=1;i<=n;i++)
            f[i][i]=1;
        for(int i=1;i<=n-1;i++)
            f[i][i+1]=(s[i]==s[i+1]?3:2);
        for(int l=3;l<=n;l++)
            for(int i=1;i<=n-l+1;i++){
                int j=i+l-1;
                f[i][j]=f[i+1][j]+f[i][j-1]-f[i+1][j-1];
                if(s[i]==s[j])
                    f[i][j]+=f[i+1][j-1]+1;
            }
        printf("Case %d: %lld\n",no,f[1][n]);
    }
    return 0;
}
