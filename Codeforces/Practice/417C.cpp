#include <stdio.h>
#include <vector>

using namespace std;

typedef pair<int, int> ii;

int n, k, u, v, a[1024][1024];
vector<ii> edge;

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i++) {
    u = i;
    for (int j = 1; j <= k; j++) {
      v = (u + j) % n;
      if (a[u][v] == false && u != v) {
        a[u][v] = true;
        a[v][u] = true;
        edge.push_back(ii(u, v));
      } else {
        puts("-1");
        return 0;
      }
    }
  }

  printf("%d\n", (int) edge.size());
  for (int i = 0; i < (int) edge.size(); i++)
    printf("%d %d\n", edge[i].first + 1, edge[i].second + 1);
  return 0;
}
