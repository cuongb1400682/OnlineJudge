#include <bits/stdc++.h>
using namespace std;

#define MOD  1000000007LL
#define BASE 283LL
#define SZ   5005

typedef long long ll;

char s[SZ];
int n, hashLeft[SZ], hashRight[SZ], powBase[SZ], sum[SZ][SZ], cross[SZ][SZ];

int hash(int L, int R, const int *h) {
	if (L < 1)
		return h[R];
	int tmp = h[R];
	tmp -= (ll) h[L - 1] * powBase[R - L + 1] % MOD;
	tmp %= MOD;
	return tmp < 0 ? tmp + MOD : tmp;
}

bool isPalind(int L, int R) {
	return hash(L, R, hashLeft) == hash(n - 1 - R, n - 1 - L, hashRight);
}

void initHash() {
	hashLeft[0] = s[0];
	hashRight[0] = s[n - 1];
	powBase[0] = 1;
	for (int i = 1; i < n; i++) {
		hashLeft[i] = ((ll) hashLeft[i - 1] * BASE % MOD + s[i]) % MOD;
		hashRight[i] =
				((ll) hashRight[i - 1] * BASE % MOD + s[n - 1 - i]) % MOD;
		powBase[i] = ((ll) powBase[i - 1] * BASE % MOD);
	}
}

void countSeg() {
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (isPalind(i, j))
				sum[j][j - i + 1]++;
	for (int i = 0; i < n; i++)
		for (int j = n - 1; j >= 0; j--)
			sum[i][j] += sum[i][j + 1];
	for (int i = 1; i < n; i++)
		sum[i][0] += sum[i - 1][0];
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			cross[j][i] = cross[j - 1][i] + sum[j][j - i + 2];
}

void print() {
	int nQuery, L, R;
	scanf("%d", &nQuery);
	while (nQuery--) {
		scanf("%d%d", &L, &R);
		L--, R--;
		printf("%d\n", sum[R][0] - sum[L][0] - cross[R][L] + R - L + 1);
	}
}

int main(void) {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif
	scanf(" %s ", s);
	n = strlen(s);
	initHash();
	countSeg();
	print();
	return 0;
}

