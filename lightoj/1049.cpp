#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define SZ 128

int a[SZ][SZ], t, n;
bool vis[SZ];
vector<int> C;

void get_circuit(int u) {
    if (vis[u]) 
	return;
    vis[u] = true;
    C.push_back(u);
    for (int v = 1; v <= n; v++)
	if (a[u][v] || a[v][u])
	    get_circuit(v);
}

int main() {
    int no = 1;
    scanf("%d", &t);
    while (t--) {
	scanf("%d", &n);
	memset(a, 0, sizeof(a));
	for (int i = 0; i < n; i++) {
	    int u, v;
	    scanf("%d %d", &u, &v); 
	    scanf("%d", &a[u][v]);
	}
	memset(vis, 0, sizeof(vis));
	C.clear();
	get_circuit(1);
	C.push_back(1);
	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i < (int) C.size() - 1; i++) {
	    int u = C[i], v = C[i + 1];
	    if (a[u][v] != 0)
		sum1 += a[u][v];
	    else
		sum2 += a[v][u];
	}
	printf("Case %d: %d\n", no++, min(sum1, sum2));
    }
    return 0;
}

