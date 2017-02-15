#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<string>
using namespace std;

struct State{
    double R,S,P;
    State(double R=0,double S=0,double P=0):
        R(R),S(S),P(P){}
};

State dp[105][105][105];
int R,S,P;

void update(State &a,double prob,State b){
    a.R+=prob*b.R;
    a.S+=prob*b.S;
    a.P+=prob*b.P;
}

State solve(int R,int S,int P){
    if(dp[R][S][P].R!=-1)
        return dp[R][S][P];
    double sum=R+S+P;
    if(R==sum)
        return State(1,0,0);
    if(S==sum)
        return State(0,1,0);
    if(P==sum)
        return State(0,0,1);
    State ans(0,0,0);
    sum=R*S+R*P+S*P;
    if(R>=1&&S>=1){ // Rock kills Scissor
        double c=R*S/sum;
        update(ans,c,solve(R,S-1,P));
    }
    if(R>=1&&P>=1){ // Paper kills Rock
        double c=R*P/sum;
        update(ans,c,solve(R-1,S,P));
    }
    if(S>=1&&P>=1){ // Scissor kills Paper
        double c=S*P/sum;
        update(ans,c,solve(R,S,P-1));
    }
    return dp[R][S][P]=ans;
}

int main(){
    while(cin>>R>>S>>P){
        for(int i=0;i<=R;i++)
            for(int j=0;j<=S;j++)
                for(int k=0;k<=P;k++)
                    dp[i][j][k]=State(-1,-1,-1);
        State ans=solve(R,S,P);
        cout<<fixed
            <<setprecision(9)
            <<ans.R<<" "
            <<ans.S<<" "
            <<ans.P<<'\n';
    }
    return 0;
}
