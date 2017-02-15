#include <bits/stdc++.h>
using namespace std;

#define SZ 1024
#define INF 0x3f3f3f3f

int f[SZ], a[SZ], g[SZ], n, t;

int main() {
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);

		int ans = -INF;
		
		f[1] = 0;
		for (int i = 2; i <= n; i++) {
			f[i] = max(f[i - 1], f[i - 2] + a[i]);
			ans = max(ans, f[i]);
		}

		g[n] = 0;
		g[1] = a[1];
		for (int i = 2; i <= n - 1; i++) {
			g[i] = max(g[i - 1], g[i - 2] + a[i]);
			ans = max(ans, g[i]);
		}

		printf("Case %d: %d\n", no, ans);
	}
	return 0;
}
