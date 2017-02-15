#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define MAX_N 2005

typedef long long ll;

int a[MAX_N][MAX_N], n, m, t, lft[MAX_N], rht[MAX_N];
char buf[MAX_N];

int calc(const int *a, int n) {
	stack<pair<int, int> > s;

	memset(lft, 0, sizeof(lft));
	memset(rht, 0, sizeof(rht));

	s.push(make_pair(a[1], 1));
	lft[1] = 1;
	for (int i = 2; i <= n; i++) {
		lft[i] = i;
		while (!s.empty() && s.top().first >= a[i]) {
			lft[i] = s.top().second;
			s.pop();
		}
		s.push(make_pair(a[i], lft[i]));
	}

	s = stack<pair<int, int> >();
	s.push(make_pair(a[n], n));
	rht[n] = n;
	for (int i = n - 1; i >= 1; i--) {
		rht[i] = i;
		while (!s.empty() && s.top().first >= a[i]) {
			rht[i] = s.top().second;
			s.pop();
		}
		s.push(make_pair(a[i], rht[i]));
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, (rht[i] - lft[i] + 1) * a[i]);
	return ans;
}

int main() {
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d %d\n", &m, &n);
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= m; i++) {
			scanf("%s", buf);
			for (int j = 0; j < n; j++) {
				a[i][j + 1] = '1' - buf[j];
			}
		}
		int ans = 0;
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++)
				if (a[i][j] == 1)
					a[i][j] += a[i - 1][j];
				ans = max(ans, calc(a[i], n));
		}
		printf("Case %d: %d\n", no, ans);
	}
	return 0;
}
