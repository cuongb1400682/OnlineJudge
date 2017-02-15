/*
 * PROB: LightOJ - 1183 - Computing Fast Average
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(ll i=ll(a),n##i=ll(b);i<=n##i;i++)
#define per(i,a,b) for(ll i=ll(a),n##i=ll(b);i>=n##i;i--)
#define ms(f,a) memset(f,a,sizeof(f))
#define reads(s) fgets(s,sizeof(s),stdin)
#define INF 0x3f3f3f3f
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef pair<string,string> ss;
typedef map<string,ll> msi;

struct rect_t { ll x1,y1,x2,y2; };
struct vert_t {
    ll x;
    ll i;
    bool is_left;
    vert_t(ll _x=0,ll _i=0, bool _is_left=true):x(_x),i(_i),is_left(_is_left) {}
};
struct node_t {
    ll y_min,y_max,sum;
    ll value;
};
struct segtree_t {
    vector<node_t> st;
    void create(const vi &Y) {
        ll n=Y.size();
        ll m=4*(ll)pow(2,floor(log(n)/log(2))+1);
        st.assign(m,node_t());
        create(Y,1,0,n-2);
    }
    void create(const vi &Y,ll node,ll L,ll R) {
        if(L==R) {
            st[node].y_min=Y[L];
            st[node].y_max=Y[L+1];
            st[node].sum=0;
            st[node].value=0;
            return;
        }
        ll M=(L+R)>>1;
        create(Y,2*node,L,M);
        create(Y,2*node+1,M+1,R);
        st[node].y_min=st[2*node].y_min;
        st[node].y_max=st[2*node+1].y_max;
    }
    void inc(ll node,ll L,ll R,ll u,ll v) {
        if(u>=st[node].y_max||v<=st[node].y_min) return;
        if(u<=st[node].y_min&&v>=st[node].y_max) {
            st[node].value++;
            st[node].sum=st[node].y_max-st[node].y_min;
            return;
        }
        ll M=(L+R)>>1;
        inc(2*node,L,M,u,v);
        inc(2*node+1,M+1,R,u,v);
        if(st[node].value==0)
            st[node].sum=st[2*node].sum+st[2*node+1].sum;
    }
    void dec(ll node,ll L,ll R,ll u,ll v) {
        if(u>=st[node].y_max||v<=st[node].y_min) return;
        if(u<=st[node].y_min&&v>=st[node].y_max) {
            st[node].value--;
            if(st[node].value==0) {
                if(L==R)
                    st[node].sum=0;
                else
                    st[node].sum=st[2*node].sum+st[2*node+1].sum;
            }
            return;
        }
        ll M=(L+R)>>1;
        dec(2*node,L,M,u,v);
        dec(2*node+1,M+1,R,u,v);
        if(st[node].value==0)
            st[node].sum=st[2*node].sum+st[2*node+1].sum;
    }
};

vector<rect_t> R;
vector<vert_t> X;
vi Y;
segtree_t s;

void readf() {
    ll N;
    scanf("%lld",&N);
    R.assign(N,rect_t());
    X.clear();
    Y.clear();
    rep(i,0,N-1) {
        scanf("%lld %lld %lld %lld",&R[i].x1,&R[i].y1,&R[i].x2,&R[i].y2);
        X.push_back(vert_t(R[i].x1,i,true));
        X.push_back(vert_t(R[i].x2,i,false));
        Y.push_back(R[i].y1);
        Y.push_back(R[i].y2);
    }
}

bool cmp(vert_t a, vert_t b) { return a.x<b.x; }

ll solve() {
    sort(X.begin(),X.end(),cmp);
    sort(Y.begin(),Y.end());
    for(ll i=0;i<(ll)Y.size();i++)
        while(i<(ll)Y.size()-1 && Y[i]==Y[i+1])
           Y.erase(Y.begin()+i);
    s.create(Y);
    ll ans=0;
    rep(i,0,X.size()-2) {
        ll id=X[i].i;
        if(X[i].is_left)
            s.inc(1,0,Y.size()-2,R[id].y1,R[id].y2);
        else
            s.dec(1,0,Y.size()-2,R[id].y1,R[id].y2);
        ans+=s.st[1].sum*(X[i+1].x-X[i].x);
    }
    return ans;
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    ll T;
    scanf("%lld",&T);
    for(ll test=1;test<=T;test++) {
        readf();
        printf("Case %lld: %lld\n",test,solve());
    }
    return 0;
}
