#include <stdio.h>
#include <algorithm>
using namespace std;

typedef long long ll;

#define SZ 10005
#define INF 0x3f3f3f3f3f3f3f3fLL

struct MinMaxTree {
	MinMaxTree(const ll *a, ll n) {
		init(a, 1, 1, n);
		this->n = n;
	}

	MinMaxTree() { }

	ll get_min(ll u, ll v) {
		if (u == 0)
			return min(query(1, 1, n, u, v).min, 0LL);
		else
			return query(1, 1, n, u, v).min;
	}

	ll get_max(ll u, ll v) {
		if (u == 0)
			return max(query(1, 1, n, u, v).max, 0LL);
		else
			return query(1, 1, n, u, v).max;
	}

private:
	struct Node {
		ll min, max;
		Node(ll _min = 0, ll _max = 0) {
			min = _min;
			max = _max;
		}
	} st[4 * SZ];
	ll n;

	Node mix(Node a, Node b) {
		Node ans;
		ans.min = min(a.min, b.min);
		ans.max = max(a.max, b.max);
		return ans;
	}
	
	void init(const ll *a, ll p, ll L, ll R) {
		if (L == R) {
			st[p].min = a[L];
			st[p].max = a[L];
			return;
		}
		ll mid = (L + R) >> 1;
		init(a, 2 * p, L, mid);
		init(a, 2 * p + 1, mid + 1, R);
		st[p] = mix(st[2 * p], st[2 * p + 1]);
	}

	Node query(ll p, ll L, ll R, ll u, ll v) {
		if (v < L || R < u)
			return Node(INF, -INF);
		if (u <= L && R <= v)
			return st[p];
		ll mid = (L + R) >> 1;
		Node left = query(2 * p, L, mid, u, v);
		Node right = query(2 * p + 1, mid + 1, R, u, v);
		return mix(left, right);
	}
};

struct MaxSumTree {
	MaxSumTree(const ll *a, ll n) {
		this->n = n;
		init(a, 1, 1, n);
	}

	MaxSumTree() { }

	ll get_max(ll u, ll v) {
		return query(1, 1, n, u, v).max;
	}
private:
	struct Node {
		ll leftMax, rightMax, max, sum;
		Node(ll leftMax = 0, ll rightMax = 0, ll max = 0, ll sum = 0):
			leftMax(leftMax), rightMax(rightMax), max(max), sum(sum) { }
	} st[4 * SZ];
	ll n;

	Node mix(Node a, Node b) {
		if (a.sum == INF)
			return b;
		if (b.sum == INF)
			return a;
		Node ans;
		ans.sum = a.sum + b.sum;
		ans.leftMax = max(a.leftMax, a.sum + b.leftMax);
		ans.rightMax = max(b.rightMax, b.sum + a.rightMax);
		ans.max = max(max(a.max, b.max), a.rightMax + b.leftMax);
		return ans;
	}
	
	void init(const ll *a, ll p, ll L, ll R) {
		if (L == R) {
			st[p] = Node(a[L], a[L], a[L], a[L]);
			return;
		}
		ll mid = (L + R) >> 1;
		init(a, 2 * p, L, mid);
		init(a, 2 * p + 1, mid + 1, R);
		st[p] = mix(st[2 * p], st[2 * p + 1]);
	}

	Node query(ll p, ll L, ll R, ll u, ll v) {
		if (v < L || R < u)
			return Node(INF, INF, INF, INF);
		if (u <= L && R <= v)
			return st[p];
		ll mid = (L + R) >> 1;
		return mix(query(2 * p, L, mid, u, v), 
				   query(2 * p + 1, mid + 1, R, u, v));
	}
};

MaxSumTree mst;
MinMaxTree mmt;
ll a[SZ], S[SZ], t, q, n;

int main() {
	scanf("%lld", &t);
	while (t--) {
		scanf("%lld", &n);
		S[0] = 0;
		for (ll i = 1; i <= n; i++) {
			scanf("%lld", &a[i]);
			S[i] = S[i - 1] + a[i];
		}

		mst = MaxSumTree(a, n);
		mmt = MinMaxTree(S, n);

		scanf("%lld", &q);
		for (ll i = 1; i <= q; i++) {
			ll x1, y1, x2, y2;
			scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
			if (x1 == y1 && y1 == x2 && x2 == y2) {
				printf("%lld\n", a[x1]);
			} else if (x2 > y1) {
				printf("%lld\n", mmt.get_max(x2, y2)-mmt.get_min(x1-1, y1-1));
			} else {
				ll tmp1 = mmt.get_max(y1, y2) - mmt.get_min(x1-1, y1-1);
				ll tmp2 = mmt.get_max(x2, y1) - mmt.get_min(x1-1, x2-1);
				ll tmp3 = mst.get_max(x2, y1);
				printf("%lld\n", max(tmp1, max(tmp2, tmp3)));
			}
		}
	}
	return 0;
}

