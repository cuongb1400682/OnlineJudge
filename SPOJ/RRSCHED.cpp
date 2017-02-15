#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;

typedef long long ll;

#define SZ 50005
#define INF 0x3f3f3f3f3f3f3f3fLL

struct Elm {
	ll value, i;
};

Elm a[SZ];
ll bit[SZ], n, x[SZ];

bool a_cmp_value(Elm a, Elm b) {
	return a.value < b.value;
}

ll query(ll x, ll y) {
	ll ans = 0;
	for (; y > 0; y -= (y & -y))
		ans += bit[y];
	for (x--; x > 0; x -= (x & -x))
		ans -= bit[x];
	return ans;
}

void update(ll x, ll value) {
	for (; x <= n; x += (x & -x))
		bit[x] += value;
}

int main() {
	memset(bit, 0, sizeof(bit));
	scanf("%lld", &n);
	for (ll i = 1; i <= n; i++) {
		scanf("%lld", &a[i].value);
		a[i].i = i;
		update(i, 1);
	}
	sort(a+ 1, a + n+1, a_cmp_value);
	ll total = 0;
	ll end = 0, start = 0;
	a[n + 1].value = INF;
	for (ll i = 1, j; i <= n; i++) {
		ll min_value = a[i].value - total;
		end += min_value * query(1, n);
		start = end - query(1, n) + 1;
		for (j = i; j <= n; j++) {
			if (a[i].value != a[j].value)
				break;
			x[a[j].i] = start + query(1, a[j].i) - 1;
		}		
		
		for (j = i; j <= n; j++) {
			if (a[i].value != a[j].value)
				break;
			update(a[j].i, -1);
		}
		
		total = a[i].value;
		i = j - 1;
	}
	for (ll i = 1; i <= n; i++)
		printf("%lld\n", x[i]);
	return 0;
}
