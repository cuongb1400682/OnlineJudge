#include<stdio.h>
#include<string.h>

int n,m,a[105],c[1005],cnt[100005];
char f[100005];

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&c[i]);
        memset(f,0,sizeof(f));
        f[0]=1;
        for(int i=1;i<=n;i++){
            memset(cnt,0,sizeof(cnt));
            for(int j=0;j+a[i]<=m;j++){
                if(f[j]&&!f[j+a[i]]&&cnt[j]<c[i]){
                    f[j+a[i]]=1;
                    cnt[j+a[i]]=cnt[j]+1;
                }
            }
        }
        int ans=0;
        for(int i=1;i<=m;i++)
            if(f[i])ans++;
        printf("Case %d: %d\n",no,ans);
    }
    return 0;
}
