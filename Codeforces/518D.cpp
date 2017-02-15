#include<stdio.h>
#include<math.h>
#include<iostream>
#include<iomanip>
using namespace std;

double f[2005][2005];
int n,t;
double p;

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    while(cin>>n>>p>>t){
        f[0][0]=1;
        for(int i=1;i<=t;i++)
            f[i][0]=f[i-1][0]*(1-p);

        for(int i=0;i<=t;i++){
            for(int j=0;j<=n;j++){
                if(i>0&&j>0){
                    f[i][j]=f[i-1][j-1]*p;
                    if(j==n)
                        f[i][j]+=f[i-1][n];
                    else
                        f[i][j]+=f[i-1][j]*(1-p);
                }
            }
        }
        
        double ans=0.0;
        for(int i=1;i<=n;i++)
            ans+=i*f[t][i];
        cout<<fixed<<setprecision(16)<<ans<<'\n';
    }
    return 0;
}
