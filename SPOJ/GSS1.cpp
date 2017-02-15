#include <bits/stdc++.h>
using namespace std;

#define SZ 50005
#define INF 0x3f3f3f3f

typedef long long ll;

struct Node {
	ll leftMax, rightMax, max, sum;
	Node(ll leftMax, ll rightMax, ll max, ll sum) {
		this->leftMax = leftMax;
		this->rightMax = rightMax;
		this->max = max;
		this->sum = sum;
	}
	Node() { }
} st[4 * SZ];

ll a[SZ], n, q;

Node mix(Node left, Node right) {
	Node ans;
	ans.sum = left.sum + right.sum;
	ans.leftMax = max(left.leftMax, left.sum + right.leftMax);
	ans.rightMax = max(right.rightMax, right.sum + left.rightMax);
	ans.max = max(max(left.max, right.max), left.rightMax + right.leftMax);
	return ans;
}

void printf(Node a) {
	printf("left = %lld, right = %lld, sum = %lld\n",
		   a.leftMax, a.rightMax, a.sum);
}

void printf(ll p, ll L, ll R, string i = "") {
	printf("%s[%lld, %lld] -> ", i.c_str(), L, R);
	printf(st[p]);
	if (L == R) return;
	ll mid = (L + R) >> 1;
	printf(2 * p, L, mid, i + "   .");
	printf(2 * p + 1, mid + 1, R, i + "   .");
}

void init(ll p, ll L, ll R) {
	st[p] = Node();
	if (L == R) {
		st[p] = Node(a[L], a[L], a[L], a[L]);
		return;
	}
	ll mid = (L + R) >> 1;
	init(2 * p, L, mid);
	init(2 * p + 1, mid + 1, R);
	st[p] = mix(st[2 * p], st[2 * p + 1]);
}

Node query(ll p, ll L, ll R, ll u, ll v) {
	if (v < L || R < u)
		return Node(INF, INF, INF, INF);
	if (u <= L && R <= v) {
//		printf("%lld %lld ", L, R);
//		printf(st[p]);
		return st[p];
	}
	ll mid = (L + R) >> 1;
	Node left = query(2 * p, L, mid, u, v);
	Node right = query(2 * p + 1, mid + 1, R, u, v);
	if (left.sum == INF)
		return right;
	if (right.sum == INF)
		return left;
	return mix(left, right);
}


int main() {
	scanf("%lld", &n);

	for (ll i = 1; i <= n; i++)
		scanf("%lld", &a[i]);

	init(1, 1, n);

	scanf("%lld", &q);
	for (ll i = 1; i <= q; i++) {
		ll u, v;
		scanf("%lld %lld", &u, &v);
		printf("%lld\n", query(1, 1, n, u, v).max);
	}

	return 0;
}
