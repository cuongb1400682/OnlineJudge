#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 100005

int t, n, d;
deque<pair<int, int> > q_min, q_max;

int main() {
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d %d", &n, &d);
		q_min.clear();
		q_max.clear();
		int ans = 0;
		for (int i = 1, number; i <= n; i++) {
			scanf("%d", &number);
			while (!q_min.empty() && q_min.back().first >= number)
				q_min.pop_back();
			q_min.push_back(make_pair(number, i));
			while (!q_max.empty() && q_max.back().first <= number)
				q_max.pop_back();
			q_max.push_back(make_pair(number, i));
			if (i >= d) {
				while (q_min.front().second < i - d + 1)
					q_min.pop_front();
				while (q_max.front().second < i - d + 1)
					q_max.pop_front();
				ans = max(ans, q_max.front().first - q_min.front().first);
			}
		}
		printf("Case %d: %d\n", no, ans);
	}
	return 0;
}
