#include <bits/stdc++.h>
using namespace std;

#define EPS (1e-7)
#define EQU(a, b) (fabs((a) - (b)) < EPS)

double a, b, c, k;

double area(double a, double b, double c) {
    double p = (a + b + c) * 0.5;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double solve() {
    double up, down, mid, S1, S;
    up = 0.0;
    down = 1.0;
    S = area(a, b, c);
    while (up <= down) {
	mid = (up + down) * 0.5;
	S1 = area(a * mid, b * mid, c * mid);
	if (EQU(S1 / (S - S1), k))
	    return a * mid;
	if (S1 / (S - S1) > k)
	    down = mid;
	else
	    up = mid;
    }
}

int main(void) {
    int nCase;
    scanf("%d", &nCase);
    for (int no = 1; no <= nCase; no++) {
	scanf("%lf %lf %lf %lf", &a, &b, &c, &k);
	printf("Case %d: %.9lf\n", no, solve());
    }
    return 0;
}
