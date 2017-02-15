#include<iostream>
#include<iomanip>
using namespace std;

#define N 10005

int s[N],n,m,h,sum;

long double solve(int n,int m){
    long double t1=1.0;
    int i=1,j=1;
    while(i<=n){
        t1*=(long double)i/j;
        i++;
        j++;
    }
    while(j<=m){
        t1*=(long double)1/j;
        j++;
    }
    return t1;
}

int main(){
    while(cin>>n>>m>>h){
        for(int i=1;i<=m;i++)
            cin>>s[i];
        s[h]--;
        sum=0;
        for(int i=1;i<=m;i++){
            sum+=s[i];
        }
        if(sum+1<n){
            cout<<-1<<'\n';
            continue;
        }
        if(s[h]==0){
            cout<<0<<'\n';
            continue;
        }
        if(sum==n-1){
            cout<<1<<'\n';
            continue;
        }
        int k=n-1;
        cout<<1-solve(sum-k,sum)/solve(sum-s[h]-k,sum-s[h])<<'\n';
    }
    return 0;
}
