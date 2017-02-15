#include <bits/stdc++.h>
using namespace std;

#define REP(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define PER(i,a,b) for(int i=int(a),n##i=int(b);i>=n##i;i--)
#define TR(it,c) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
#define ms(f,a) memset(f,a,sizeof(f))
#define reads(s) fgets(s,sizeof(s),stdin)
#define DBG(S) cerr << "[" #S " = " << (S) << "]" << endl;
#define INF 0x3f3f3f3f
#define MOD 100003
#define SZ 200000
#define EPS (double)(1e-6)
#define fi first
#define se second
#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef list<int> li;
typedef set<int> si;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef map<string, int> msi;
typedef pair<string, string> ss;
typedef map<int, int> mii;

struct data_t {
    int L, R, nChildren;
    data_t(int _L = 0, int _R = 0, int _nChildren = 0) :
            L(_L), R(_R), nChildren(_nChildren) {
    }
};

map<ii, data_t> data;
mii link;
int N, lable[100001], nGroup;
char a[788895];
map<int, vii> bucket;

void parse(const char *str, mii &prs) {
    stack<int> s;
    for (const char *p = str; *p; p++) {
        if (*p == '(')
            s.push(p - str);
        else if (*p == ')') {
            int pos = s.top();
            s.pop();
            int curp = p - str;
            prs[pos] = curp;
            prs[curp] = pos;
        }
    }
}

int getHash(int m, int M) {
    if (m > M)
        swap(m, M);
    int N = M - m + 1;
    int hash = ((ll) (m * N + N * (N - 1) / 2)) % MOD;
    return ((ll) hash * hash) % MOD;
}

ii fillBucket(int L, int R, mii& link_a) {
    if (L >= R)
        return ii(INF, -INF);
    int m = INF, M = -INF;
    REP(i,L+1,R-1)
    {
        if (a[i] == '(') {
            ii tmp = fillBucket(i, link_a[i], link_a);
            i = link_a[i];
            m = min(m, tmp.fi);
            M = max(M, tmp.se);
        } else if (isdigit(a[i])) {
            int y;
            for (y = 0; isdigit(a[i]); i++)
                y = y * 10 + (a[i] - '0');
            y = lable[y];
            m = min(m, y);
            M = max(M, y);
        }
    }
    bucket[getHash(m, M)].pb(ii(m, M));
    return ii(m, M);
}

void browseBob(int L, int R) {
    if (L >= R)
        return;

    data_t &ans = data[ii(L, R)];
    ans.L = INF, ans.R = -INF, ans.nChildren = 0;

    REP(i,L+1,R-1)
    {
        if (a[i] == '(') {
            browseBob(i, link[i]);
            data_t &tmp = data[ii(i, link[i])];
            ans.nChildren += tmp.nChildren;
            if (ans.L > tmp.L)
                ans.L = tmp.L;
            if (ans.R < tmp.R)
                ans.R = tmp.R;
            i = link[i];
        } else if (isdigit(a[i])) {
            int num;
            for (num = 0; isdigit(a[i]); i++)
                num = num * 10 + (a[i] - '0');
            num = lable[num];
            if (ans.L > num)
                ans.L = num;
            if (ans.R < num)
                ans.R = num;
            ans.nChildren++;
        }
    }
}

void relable(char *a) {
    ms(lable, 0);
    int count = 0, num;
    for (char *c = a; *c; c++) {
        if (isdigit(*c)) {
            for (num = 0; isdigit(*c); c++)
                num = num * 10 + *c - '0';
            c--;
            lable[num] = ++count;
        }
    }
}

void countGroup() {
    TR(datum,data)
    {
        data_t t = datum->se;
        if (t.R - t.L + 1 == t.nChildren) {
            int hashValue = getHash(t.L, t.R);
            TR(it,bucket[hashValue])
            {
                if (t.L == it->fi && t.R == it->se) {
                    nGroup++;
                    break;
                }
            }
        }
    }
}

int main() {
    while (scanf(" %d ", &N) != EOF) {
        scanf("%s", a);
        link.clear();
        parse(a, link);
        relable(a);
        bucket.clear();
        fillBucket(0, strlen(a) - 1, link);

        scanf("%s", a);
        link.clear();
        parse(a, link);

        nGroup = N;
        if (N > 1) {
            data.clear();
            browseBob(0, strlen(a) - 1);
            countGroup();
        }
        printf("%d\n", nGroup);
    }
    return 0;
}

