class LongWordsDiv1 {
public:
    const int MOD = 1000000007;
    const int SZ = 5001;
    typedef long long ll;

    ll factorial(ll x) {
        ll ans=1;
        for(ll i=2;i<=x;i++)
            ans=ans*i%MOD;
        return ans;
    }

    ll count(ll n) {
        ll f[SZ];
        memset(f,0,sizeof f);
        f[1]=1;
        f[2]=1;
        for(ll i=3;i<=n;i++) {
            f[i]=f[i-1];
            for(ll p=1;p<=i-2;p++)
                (f[i]+=(f[p]*f[i-p-1])%MOD)%=MOD;
        }
        return f[n]*factorial(n)%MOD;
    }
};
