#include <stdio.h>
#include <string.h>

#define SZ 100005
#define MOD 1000000007LL

typedef long long ll;

ll previous[256], dp[SZ], n;
char str[SZ];

int main() {
	scanf("%lld", &n);
	while (n--) {
		str[0] = '$';
		scanf("%s", str + 1);
		ll len = strlen(str + 1);
		memset(dp, 0, sizeof(dp));
		memset(previous, 0, sizeof(previous));
		dp[0] = 1;
		for (ll i = 1; i <= len; i++) {
			dp[i] = 2 * dp[i - 1] % MOD;
			if (previous[str[i]] > 0)
				dp[i] = (dp[i] - dp[previous[str[i]] - 1] + MOD) % MOD;
			previous[str[i]] = i;
		}
		printf("%lld\n", dp[len]);
	}
	return 0;
}
