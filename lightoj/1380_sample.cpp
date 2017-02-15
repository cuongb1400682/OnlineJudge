#include <bits/stdc++.h> 
 
#define MAX 1010
 
using namespace std;
 
 
struct edge
{
    int v, w;
    bool operator < ( const edge &u ) const { return w > u.w; }
};
 
vector <edge > G[MAX] ;
 
vector<int> GT[MAX] ;
 
char clr[MAX] ;
 
int n,root  ;
 
int DMST() {
 
    int i, res=0, pr[MAX], cost[MAX], sub[MAX], sn[MAX], visited[MAX];
    vector <int> ::iterator v, it;
    vector <int> node[MAX];
 
    for(i = 0; i <= n; i++) {
        node[i].clear();
        node[i].push_back( i );
        sn[i] = i, sub[i] = pr[i] = 0;
    }
 
    for(i = 1; i <= n; i++) if( i != root ) {
            sort( G[i].begin(), G[i].end() );
            pr[i] = G[i].back().v;
            cost[i] = sub[i] = G[i].back().w;
            res += cost[i];
    }
 
    bool cycle = true;
 
    while( cycle ) {
 
        cycle = false;
        memset( visited, 0, sizeof( visited ) );
        for(i = 1; i <= n; i++) {
            if( visited[i] || sn[i] != i ) continue;
            int cur = i;
            do {
                visited[cur] = i;
                cur = pr[cur];
            } while( cur > 0 && !visited[ cur ] );
            if( cur > 0 && visited[ cur ] == i ) {
                cycle = true;
                int start = cur;
                do {
                    if( *node[cur].begin() != cur ) break;
                    for( it = node[cur].begin(); it != node[cur].end(); it++) {
                        sn[ *it ] = start;
                        if( cur != start ) node[ start ].push_back ( *it );
                    }
                    if( cur != start ) node[ cur ].clear();
                    cur = pr[ cur ];
                } while( cur != start );
                int best = INT_MAX;
                for( v = node[start].begin(); v!=node[start].end(); v++) {
                    while( !G[*v].empty() && sn[G[*v].back().v] == start)
                        G[ *v ].pop_back();
                    if( !G[*v].empty() ) {
                        int tcost = G[*v].back().w - sub[ *v ];
                        if( tcost < best ) best = tcost, pr[ start ] = G[*v].back().v;
                    }
                }
                cost[ start ] = best;
                for( v = node[start].begin(); v != node[start].end(); v++ )sub[*v] += best;
                res += best;
            }
        }
        for(i = 1; i <= n; i++) pr[i] = sn[ pr[i] ];
    }
    return res;
}
 
int cnt ;
 
void dfs(int u) {
    clr[u] = 1 ;
    cnt ++ ;
    int i,v ;
    for(int i=0; i<GT[u].size(); i++) {
        v = GT[u][i] ;
        if(clr[v]) continue ;
        dfs(v) ;
    }
}
 
 
int main() {
    int T,t=1,m,i,j,k;
 
    scanf("%d",&T);
 
    for(t=1; t<=T; t++) {
 
        scanf("%d%d%d",&n,&m,&root);
 
        root ++ ;
 
        for(int i=1; i<=n; i++)    G[i].clear() ;
        for(int i=1; i<=n; i++)   GT[i].clear() ;
 
        while(m--) {
 
            scanf("%d%d%d",&j,&i,&k);
 
            i++;
            j++;
 
            edge u ;
 
            u.v = j ;
            u.w = k ;
 
            G[i].push_back(u) ;
            GT[j].push_back(i) ;
        }
 
 
        for(int i=1; i<=n; i++)      clr[i] = 0 ;
 
        cnt  = 0 ;
        dfs(root) ;
 
        if(cnt>=n)   printf("Case %d: %d\n",t,DMST());
        else         printf("Case %d: impossible\n",t);
    }
    return 0;
}
