#include<iostream>
#include<iomanip>
using namespace std;

#define MAX_N 1005

double dp[MAX_N][MAX_N];

double probability(int B,int W){
    if(dp[B][W]!=-1){
        return dp[B][W];
    }
    if(W==0){
        return dp[B][W]=0.0;
    }
    if(B==0){
        return dp[B][W]=1.0;
    }
    double P=(double)W/(B+W);
    double c=((double)B/(B+W))*((double)(B-1)/(B+W-1));
    double D=0;
    if(B>=2 && W>=1) // a white mouse jumps out
        D+=c*probability(B-2,W-1)*((double)W/(W+B-2));
    if(B>=3 && W>=0) // a black mouse jumps out
        D+=c*probability(B-3,W)*((double)(B-2)/(W+B-2));
    return dp[B][W]=P+D;
}

int main(){
    ios::sync_with_stdio(0);
    int w,b;
    while(cin>>w>>b){
        for(int i=0;i<=b;i++)
            for(int j=0;j<=w;j++)
                dp[i][j]=-1.0;
        cout<<fixed<<setprecision(9)<<probability(b,w)<<'\n';
    }
    return 0;
}
