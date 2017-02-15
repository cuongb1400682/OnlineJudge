#include<stdio.h>
#include<string.h>

#define INF 0x3f3f3f3f
#define N 1024

char s[N];
int n,f[N];
bool is_palind[N][N];

int min(int a,int b){
    return a>b?b:a;
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%s",s+1);
        int n=strlen(s+1);

        memset(is_palind,0,sizeof(is_palind));
        memset(f,0x3f,sizeof(f));

        for(int i=1;i<=n;i++){
            is_palind[i][i]=true;
            is_palind[i][i+1]=(i+1<=n&&s[i]==s[i+1]);
        }
        
        for(int l=3;l<=n;l++)
            for(int i=1;i<=n-l+1;i++){
                int j=i+l-1;
                is_palind[i][j]=(s[i]==s[j]&&is_palind[i+1][j-1]);
            }

        f[0]=0;
        f[1]=1;
        for(int i=2;i<=n;i++)
            for(int j=i;j>=1;j--)
                if(is_palind[j][i])
                    f[i]=min(f[i],f[j-1]+1);

        printf("Case %d: %d\n",no,f[n]);
    }
    return 0;
}
