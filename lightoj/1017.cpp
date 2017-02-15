#include<stdio.h>
#include<string.h>
#include<map>
using namespace std;

#define INF 1000000000
#define N 101

typedef pair<int,int> ii;

int f[N][N],S[N],y[N],next[N],n,w,k;
    
int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        scanf("%d%d%d",&n,&w,&k);

        map<int,int> cnt;
        for(int i=1;i<=n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            cnt[v]++;
        }
        n=0;

        if(k==0){
            printf("Case %d: %d\n",no,0);
            continue;
        }

        memset(f,0,sizeof(f));
        y[0]=-INF;
        S[0]=0;
        for(map<int,int>::iterator it=cnt.begin();it!=cnt.end();it++){
            y[++n]=it->first;
            S[n]=S[n-1]+it->second;
        }
        y[++n]=INF;
        S[n]=S[n-1];

        int ans=-INF;
        
        for(int i=1;i<=n-1;i++){
            for(int j=i+1;j<=n;j++)
                if(y[i]+w<y[j]){
                    next[i]=j-1;
                    break;
                }
            f[1][i]=S[next[i]]-S[i-1];
            if(ans<f[1][i])
                ans=f[1][i];
        }

        for(int h=2;h<=k;h++){
            for(int i=1;i<=n;i++){
                for(int j=next[i]+1;j<=n;j++)
                    f[h][i]=max(f[h][i],f[h-1][j]+S[next[i]]-S[i-1]);
                if(ans<f[h][i])
                    ans=f[h][i];
            }
        }

        printf("Case %d: %d\n",no,ans);
    }
    return 0;
}
