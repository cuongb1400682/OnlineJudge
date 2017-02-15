#include<stdio.h>
#include<string.h>

char s[128];
int len,f[128][128];

int max(int a,int b){
    return a>b?a:b;
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%s",s);
        len=strlen(s);
        memset(f,0,sizeof(f));
        for(int i=0;i<len;i++)
            f[i][i]=1;
        for(int l=2;l<=len;l++)
            for(int i=0;i<=len-l;i++){
                int j=i+l-1;
                if(s[i]==s[j])
                    f[i][j]=f[i+1][j-1]+2;
                else
                    f[i][j]=max(f[i+1][j],f[i][j-1]);
            }
        printf("Case %d: %d\n",no,len-f[0][len-1]);
    }
    return 0;
}
