struct PairsOfStrings {
    typedef long long ll;
    vector<int> d;
    const int M=1000000007;

    void list_divisors(int n) {
        d.clear();
        int lim=sqrt(n);
        for(int i=1;i<=lim;i++)
            if(n%i==0) {
                d.push_back(i);
                if(i!=n/i)
                    d.push_back(n/i);
            }
        sort(d.begin(),d.end());
    }

    ll pow(ll a,ll b) {
        if(b==0) return 1;
        ll x=pow(a,b/2);
        x=x*x%M;
        return (b&1)?x*a%M:x;
    }

    int getNumber(int n,int k) {
        list_divisors(n);
        vector<int> f;
        int ans=0;
        for(int i=0;i<(int)d.size();i++) {
            ll x=pow(k,d[i]); // ll for not overflowing
            for(int j=0;j<i;j++)
                if(d[i]%d[j]==0) {
                    x-=f[j];
                    if(x<0) x+=M; // be ware of the result of "-" that can be negative
                }
            f.push_back(x);
            (ans+=x*d[i]%M)%=M;
        }
        return ans;
    }
};
