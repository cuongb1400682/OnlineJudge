#include <bits/stdc++.h>
using namespace std;

#define SZ 100005
#define DBG(s) cerr << "[" #s " = " << (s) << "]" << endl
#define DBS(s) cerr << "[" << (#s) << "]" << endl
#define DBL    cerr << endl
#define ROOT(n, k) pow(n,1.0/k)

typedef long long ll;

ll P[SZ],nP,n,q;;

map<ll, ll> dp[2000];

void sieve(ll n = 1005000) {
    static bitset<1005000> isPrime;
    ll sqrtN = (ll) sqrt(n);
    isPrime.flip();
    for (ll i = 2; i <= sqrtN; i++) 
	if (isPrime[i])
	    for (ll j = i*i; j <= n; j += i)
		isPrime[j] = false;
    nP = 1;    
    for (ll i = 2; i <= n; i++)
	if (isPrime[i])
	    P[nP++] = i;
}

ll phi(ll m, ll n) {
    if (n == 0) 
	return m;  
    else if (dp[n].count(m) != 0)
	return dp[n][m];    
    else 
	return dp[n][m] = phi(m, n-1) - phi(m/P[n],n-1);
}

ll pi(ll x) {
    if (x <= P[nP-1])
	return (ll)(upper_bound(P+1, P+nP+1, x)-P-1);
    ll a = pi(ROOT(x, 4));
    ll b = pi(ROOT(x, 2));
    ll c = pi(ROOT(x, 3));
    ll ans = phi(x,a)+(b+a-2)*(b-a+1)/2;
    for (ll i = a+1; i <= b ; i++)
	ans -= pi(x / P[i]);
    for (ll i = a+1; i <= c; i++) {
	ll bi = pi(sqrt(double(x) / P[i]));
	for (ll j = i; j <= bi; j++) {
	    ans -= pi(x / P[i] / P[j]) - j + 1;
	}
    }
    return ans;
}

bool isPrime(ll number) {
    if (number <= 1) return false;
    if (number == 2 || number == 3) return true;
    if (number % 2 == 0 || number % 3 == 0) return false;    
    ll sqrt_n = (ll) sqrt(number);
    for (int k = 5; k <= sqrt_n; k += 6) {
	if (number % k == 0 || number % (k + 2) == 0)
	    return false;
    }
    return true;
}

int main(void) {
    sieve();
    scanf("%lld %lld", &n, &q);
    printf("%lld\n", pi(n));
    for (ll i = 0, nu; i < q; i++) {
	scanf("%lld", &nu);
	printf("%d\n", (int)isPrime(nu));
    }
    return 0;
}
