#include <bits/stdc++.h>
using namespace std;

#define SZ 20

int n, K, a[SZ], L1[20000], L2[20000], nL1, nL2;

void makeList(int pos, int end, int x, int *L, int &nL) {
    if (pos >= end) {
	L[nL++] = x;
	return;
    }
    for (int j = 0; j <= 2; j++) 
	makeList(pos + 1, end, a[pos] * j + x, L, nL);
}

bool solve() {
    nL1 = nL2 = 0;
    makeList(0, n/2, 0, L1, nL1);
    makeList(n/2, n, 0, L2, nL2);
    sort(L2, L2 + nL2);
    for (int i = 0; i < nL1; i++) 
	if (*lower_bound(L2, L2 + nL2, K - L1[i]) == K - L1[i])
	    return true;
    return false;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
    int nCase;
    scanf("%d", &nCase);
    for (int no = 1; no <= nCase; no++) {
	scanf("%d%d", &n, &K);
	for (int i = 0; i < n; i++)
	    scanf("%d", &a[i]);
	printf("Case %d: %s\n", no, solve() ? "Yes" : "No");
    }
    return 0;
}
