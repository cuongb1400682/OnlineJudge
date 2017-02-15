/*
 * PROB: Codeforces - 283C - Coin Troubles
 * LANG: C++
 */

#include <cstdio>
#include <cstring>

#define SZ 301
#define MOD 1000000007
#define ms(a,v) memset(a,v,sizeof a)

int n,q,t,a[SZ],f[10000000],p[SZ],d[SZ];

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(scanf("%d %d %d",&n,&q,&t)!=EOF) {
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        ms(p,0),ms(f,0),ms(d,0);
        for(int i=1,u,v;i<=q;i++)
            scanf("%d %d",&u,&v),p[u]=v,d[v]++;
        int l=0,s;
        for(int i=1;i<=n;i++)
            if (!d[i]) {
                s=0;
                for(int k=i;k>0;k=p[k],l++) {
                    a[k]=(s+=a[k]);
                    if(p[k]>0) t-=a[k];
                    if(t<0) break;
                }
                if (l<0) break;
            }
        if (l<n||t<0) {
            printf("0\n");
        } else {
            f[0]=1;
            for(int i=1;i<=n;i++)
                for(int k=a[i];k<=t;k++)
                    (f[k]+=f[k-a[i]])%=MOD;
            printf("%d\n",f[t]);
        }
    }
    return 0;
}
