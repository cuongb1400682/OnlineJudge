#include<stdio.h>
#include<math.h>
#include<ios>
#include<iostream>
#include<iomanip>
using namespace std;

#define N 100005

typedef long long ll;
typedef long double ld;

ll n,p,L,R,nn[N],f[N];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(cin>>n>>p){
        for(ll i=0;i<n;i++){
            cin>>L>>R;
            nn[i]=R-L+1;
            f[i]=(R/p)-(ll)ceil((ld)L/p)+1;
        }
        ld sum=0;
        for(ll i=0;i<n;i++){
            ll j=(i+1)%n;
            ld prob=1.0-((ld)(nn[i]-f[i])/(nn[i]*nn[j]))*(nn[j]-f[j]);
            sum+=prob;
        }
        sum*=2000.0;
        cout<<setprecision(9)<<sum<<'\n';
    }
    return 0;
}
