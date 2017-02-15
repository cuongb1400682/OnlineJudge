#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define N 2005

typedef long long ll;

ll sign(ll x){
    if(x==0)
        return 0;
    return x<0?-1:1;
}

struct Vec{
    ll x,y;
    Vec(ll _x=0,ll _y=0){
        ll i,j;
        for(i=abs(_x),j=abs(_y);i&&j;){
            if(i>j)i%=j;
            else j%=i;
        }
        i+=j;
        if(i>0){
            x=_x/i;
            y=_y/i;
        }
        if(x==0)
            y=abs(y);
        if(y==0)
            x=abs(x);
        if(sign(x)*sign(y)<0){
            x=-abs(x);
            y=abs(y);
        }
        if(sign(x)*sign(y)>0){
            x=abs(x);
            y=abs(y);
        }
    }
};

ll n,x[N],y[N],ans;

bool operator==(Vec a,Vec b){
    return (a.x==b.x)&&(a.y==b.y);
}

bool operator<(Vec a,Vec b){
    if(a.x!=b.x)
        return a.x<b.x;
    return a.y<b.y;
}

ll C3(ll n){
    return n*(n-1)*(n-2)/6;
}

ll C2(ll n){
    return n*(n-1)/2;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(ll i=0;i<n;i++)
        cin>>x[i]>>y[i];
    ans=C3(n);
    for(ll i=0;i<n;i++){
        vector<Vec> vecs;
        for(ll j=0;j<i;j++)
            vecs.push_back(Vec(x[j]-x[i],y[j]-y[i]));
        sort(vecs.begin(),vecs.end());
        ll k=1;
        for(ll j=1;j<(ll)vecs.size();j++){
            if(vecs[j]==vecs[j-1]){
                k++;
            }else{
                ans-=C2(k);
                k=1;
            }
        }
        ans-=C2(k);
    }
    cout<<ans<<'\n';
    return 0;
}
