#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define per(i,a,b) for(int i=int(a),n##i=int(b);i>=n##i;i--)
#define ms(f,a) memset(f,a,sizeof(f))
#define reads(s) fgets(s,sizeof(s),stdin)
#define D(S) cout<<S<<endl;
#define INF 0x3f3f3f3f
#define EPS (double)(1e-6)
#define fi first
#define se second
#define pb push_back
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef set<int> si;
typedef vector<ii> vii;
typedef pair<string,string> ss;
typedef map<string,int> msi;

int a[105],N;
double F[105],P[105];

double solve() {
    P[1]=1.0;
    F[1]=a[1];
    rep(i,2,N) {
        F[i]=P[i]=0.0;
        rep(j,max(1,i-6),i-1) {
            F[i]+=(F[j]+P[j]*a[i])/min(6,N-j);
            P[i]+=P[j]/min(6,N-j);
        }
    }
    return F[N];
}

int main(void) {
    int T;
    scanf("%d",&T);
    for(int test=1;T--;test++) {
        scanf("%d",&N);
        rep(i,1,N) scanf("%d",&a[i]);
        printf("Case %d: %lf\n",test,solve());
    }
    return 0;
}
