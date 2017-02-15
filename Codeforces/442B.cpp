#include<iostream>
#include<ios>
#include<iomanip>
#include<algorithm>
using namespace std;

#define N 128

long double p[N];
int n;

int main(){
    ios::sync_with_stdio(0);
    while(cin>>n){
        for(int i=0;i<n;i++)
            cin>>p[i];
        sort(p,p+n);
        if(p[n-1]==1.0){
            cout<<1.0<<'\n';
            continue;
        }            
        long double P=1.0;
        long double S=0;
        for(int i=n-1;i>=0;i--){
            long double P1=P*(1-p[i]);
            long double S1=S+p[i]/(1-p[i]);
            if(P*S<P1*S1){
                P=P1;
                S=S1;
            }
        }
        cout<<fixed<<setprecision(12)<<P*S<<'\n';
    }
}
