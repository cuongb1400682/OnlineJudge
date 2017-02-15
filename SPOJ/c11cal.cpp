#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << "[" #x " = " << x << "]" << endl
template<class T>
void __dba(const T* a, int n) {
    cerr << "[";
    for (int i = 0; i < n; i++)
	cerr << (i > 0 ? ", " : "" ) << a[i];
    cerr << "]" << endl;
}
#define dba(a, n) { cerr << #a " = "; __dba(a, n); }

#define MOD 1000000007
#define SZ 64

typedef vector<vector<int> > matrix;
typedef long long ll;

int n, k, C[SZ][SZ];
matrix A, F0;

void mk_mat(matrix &a, int n, int m, bool is_random = false) {
    a.assign(n, vector<int>());
    if (is_random) srand(clock());
    for (int i = 0; i < n; i++)
	a[i].assign(m, is_random ? rand() % 100 : 0);
}

matrix mult(const matrix& a, const matrix& b) {
    matrix c;
    int n = a.size();
    int p = a[0].size();
    int m = b[0].size();
    int tmp;
    mk_mat(c, n, m);
    for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++)
	    for (int k = 0; k < p; k++) {
		tmp = (int)((ll)a[i][k] * b[k][j] % MOD);
		c[i][j] = int(((ll)c[i][j] + tmp) % MOD);
	    }
    return c;
}

matrix powMod(matrix a, int n) {
    int first = true;
    matrix ans;
    
    if (n == 0) {
	mk_mat(ans, a.size(), a[0].size());
	for (int i = 0; i < a.size(); i++) 
	    ans[i][i] = 1;
	return ans;
    }

    for (int i = n; i > 0; i >>= 1) {
	if (i & 1) {
	    if (first)
		ans = a;
	    else
		ans = mult(ans, a);
	    first = false;
	}
	a = mult(a, a);
    }
    return ans;
}

void prepare() {
    C[0][0] = 1;
    for (int i = 1; i <= 55; i++)  {	
	for (int j = 0; j <= i; j++) {
	    if (j == 0)
		C[i][j] = 1;
	    else
		C[i][j] = ((ll)C[i - 1][j - 1] + C[i - 1][j]) % MOD;
	}
    }
}

int main(void) {
    prepare();
    while (~scanf("%d%d", &n, &k)) {
	mk_mat(F0, k + 2, 1);
	mk_mat(A, k + 2, k + 2);
	for (int i = 0; i < k + 2; i++) F0[i][0] = 1;
	int st = 1;
	for (int i = k; i >= 1; i--, st++) {
	    for (int j = 0; j <= i; j++) {
		A[st][st+j] = C[i][j];
	    }
	}
	for (int i = 0; i < k + 2; i++)
	    A[0][i] = A[1][i];
	A[0][0] = A[k+1][k+1] = 1;
	printf("%d\n", mult(powMod(A, n - 1), F0)[0][0]);
    }
    return 0;
}
