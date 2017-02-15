// some useful macros
#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,v) memset(f,v,sizeof f)
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define SZ 1001
typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> ii;

typedef int AnswerType;

struct Assemble {
    AnswerType f[101][101];
    AnswerType minCost(vi connect) {
        ms(f,0);
        connect.insert(connect.begin(),-1);
        int n=connect.size();
        rep(L,2,n-1) {
            rep(l,1,n-L-1) {
                int r=l+L-1;
                int tmp=INF;
                rep(m,l,r-1) {
                    int cost=(connect[l]+(m-l+1))*
                            connect[m+1]*(connect[r+1]+(r-m));
                    tmp=min(tmp,cost+f[l][m]+f[m+1][r]);
                }
                f[l][r]=tmp;
            }
        }
        return f[1][n-2];
    }
};
