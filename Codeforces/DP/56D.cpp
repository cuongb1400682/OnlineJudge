/*
 * PROB: Codeforces - 56D - Changing a String
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define ms(f,a) memset(f,a,sizeof f)
#define SZ 1005
#define INF 0x3f3f3f3f

int f[SZ][SZ],n,m;
char s[SZ],t[SZ];

int min3(int a,int b,int c) { return min(a,min(b,c)); }

int solve(int i,int j) {
    if(f[i][j]!=-1)
        return f[i][j];
    int t1=solve(i-1,j);
    int t2=solve(i-1,j-1);
    int t3=solve(i,j-1);
    if(s[i]==t[j])
        return f[i][j]=t2;
    return f[i][j]=min3(t1,t2,t3)+1;
}

void print(int i,int j) {
    while(i||j) {
        if(s[i]==t[j])
            i--,j--;
        else {
            if(f[i][j]==f[i][j-1]+1)
                printf("INSERT %d %c\n",i+1,t[j]),j--;
            else if(f[i][j]==f[i-1][j]+1)
                printf("DELETE %d\n",i),i--;
            else
                printf("REPLACE %d %c\n",i,t[j]),i--,j--;
        }
    }
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(~scanf("%s %s",s+1,t+1)) {
        n=strlen(s+1),m=strlen(t+1);
        ms(f,-1),f[0][0]=0;
        rep(i,1,n) f[i][0]=i;
        rep(j,1,m) f[0][j]=j;
        cout<<solve(n,m)<<endl;
        print(n,m);
    }
    return 0;
}
