/*
 * PROB: Codeforces - 18E - Flag 2 (improved version)
 * LANG: C++
 */

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define TRv(c,it) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
#define ms(f,a) memset(f,a,sizeof f)
#define INF 0x3f3f3f3f
#define SZ 505

int n,m,d[26][26],f[SZ][26][26],t[SZ][26][26],ln[SZ];
vector<int> row[SZ][2];
char buf[SZ];

int diff(int c1,int c2) {
    if(c1==c2) return INF;
    int ans=0;
    for(int i=1;i<=m;i+=2) {
        ans+=(ln[i]!=c1);
        if(i+1<=m) ans+=(ln[i+1]!=c2);
    }
    return ans;
}

// the most important heuristic
vector<pair<int,int> > cnt[2];
void statistic(int i) {
    row[i][0].clear(),row[i][1].clear();
    cnt[0].assign(26,make_pair(0,0));
    cnt[1].assign(26,make_pair(0,0));
    rep(j,1,m)
        cnt[j&1][ln[j]].first++,cnt[j&1][ln[j]].second=ln[j];
    sort(cnt[0].rbegin(),cnt[0].rend());
    sort(cnt[1].rbegin(),cnt[1].rend());
    rep(j,0,3) {
        if(cnt[0][j].first) row[i][0].push_back(cnt[0][j].second);
        if(cnt[1][j].first) row[i][1].push_back(cnt[1][j].second);
    }
    if(m>1) {
        while(row[i][0].size()<4)
            row[i][0].push_back((row[i][0].back()+1)%26);
    } else
        rep(j,0,3) row[i][0].push_back(j);
    while(row[i][1].size()<4)
        row[i][1].push_back((row[i][1].back()+1)%26);
}

int main(void) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","rt",stdin);
    freopen("output.txt","wt",stdout);
#endif
    while(cin>>n>>m) {
        ms(f,0),ms(d,0);
        rep(i,1,n) {
            // cin -> buf
            (cin>>(buf+1)).ignore();
            rep(j,1,m) ln[j]=buf[j]-'a';
            statistic(i);
            // tno changes d[][]
            TRv(row[i][1],c1)TRv(row[i][0],c2) d[*c1][*c2]=diff(*c1,*c2);
            // DP
            if(i==1) {
                memcpy(f[1],d,sizeof d);
            } else {
                TRv(row[i][1],c1)TRv(row[i][0],c2) { // CURRENT row
                    int tmp=INF,zz,zzz;
                    if(c1!=c2) TRv(row[i-1][1],c3)TRv(row[i-1][0],c4) { // PREVIOUS row
                        if(*c3!=*c4&&*c3!=*c1&&*c4!=*c2)
                            if(tmp>f[i-1][*c3][*c4]+d[*c1][*c2]) {
                                tmp=f[i-1][*c3][*c4]+d[*c1][*c2];
                                zz=*c3,zzz=*c4;
                            }
                    }
                    f[i][*c1][*c2]=tmp;
                    t[i][*c1][*c2]=zz*100+zzz;
                }
            }
        }

        int ans=INF,zz,zzz;
        TRv(row[n][1],c1)TRv(row[n][0],c2) if(ans>f[n][*c1][*c2])
            ans=f[n][*c1][*c2],zz=*c1,zzz=*c2;
        cout<<ans<<endl;
        string s="";
        for(int i=n;i>0;i--) {
            char c1=zz+'a',c2=zzz+'a';
            string ts="";
            for(int j=1;j<=m;j+=2) {
                ts.push_back(c1);
                if(j+1<=m) ts.push_back(c2);
            }
            s=ts+'\n'+s;
            // trace backward
            c1=t[i][zz][zzz]/100;
            c2=t[i][zz][zzz]%100;
            zz=c1,zzz=c2;
        }
        cout<<s<<endl;
    }
    return 0;
}
