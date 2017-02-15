#include <bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x " = " << (x) << '\n'
#define arr(x, n) {cerr<<#x<<" = "<<"["<<(n)<<"]"<<"(";for(ll _=0;_<(n);_++) cerr<<(x)[_]<<(_!=(n)-1?", ":")\n");}
#define iarr(x, m, n) {cerr<<#x":\n";for(ll _=(m);_<=(n);_++) cerr<<_<<": "<<(x)[_]<<'\n';}
#define err(...) fprintf(stderr, __VA_ARGS__)
#define SZ 100005

typedef long long ll;

struct Query {
	bool is_add;
	int val;
	Query(bool _ia = false, int _val = 0) {
		is_add = _ia;
		val = _val;
	}
};

vector<Query> query;
vector<pair<int, int> > a;
int n, q, t, st[4 * SZ];

void init(int p, int L, int R) {
	if (L == R) {
		st[p] = a[L].second;
		return;
	}
	init(2 * p, L, (L + R) / 2);
	init(2 * p + 1, (L + R) / 2 + 1, R);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int remove(int p, int L, int R, int u) {
	if (L == R) {
		st[p] = 0;
		return a[L].first;
	}
	int ans = 0;
	if (u > st[2 * p])
		ans = remove(2 * p + 1, (L + R) / 2 + 1, R, u - st[2 * p]);
	else
		ans = remove(2 * p, L, (L + R) / 2, u);
	st[p] = st[2 * p] + st[2 * p + 1];
	return ans;
}

void insert(int p, int L, int R, int u) {
	if (L == R) {
		st[p] = 1;
		return;
	}
	if (u <= (L + R) / 2)
		insert(2 * p, L, (L + R) / 2, u);
	else
		insert(2 * p + 1, (L + R) / 2 + 1, R, u);
	st[p] = st[2 * p] + st[2 * p + 1];
}

int main() {
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d %d", &n, &q);
		
		query.clear();
		a.clear();
		
		for (int i = 1; i <= n; i++) {
			a.push_back(make_pair(0, 1));
			scanf("%d", &a.back().first);
		}

		query.push_back(Query());
		for (int i = 1; i <= q; i++) {
			char tp[2]; int nu;
			scanf("%s %d", tp, &nu);
			query.push_back(Query(tp[0] == 'a', nu));
			if (tp[0] == 'a') {
				a.insert(a.end(), make_pair(nu, 0));
			}
		}
		
		a.insert(a.begin(), make_pair(-1, -1));

		int K = n+1;
		n = a.size() - 1;
		if (n > 0)
			init(1, 1, n);
		else {
			memset(st, 0, sizeof(st));
			n = 0;
		}

		printf("Case %d:\n", no);
		for (int i = 1; i <= q; i++) {
			if (query[i].is_add) {
				insert(1, 1, n, K);
				K++;
			} else { // call
				int idx = -1;
				if (query[i].val >= 1 && query[i].val <= st[1]) {
					idx = remove(1, 1, n, query[i].val);
				}
				if (idx == -1)
					puts("none");
				else
					printf("%d\n", idx);
			}
		}
	}
	return 0;
}
