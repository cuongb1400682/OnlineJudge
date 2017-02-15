#include <stdio.h>
#include <map>
#include <set>
#include <string>

using namespace std;

map<string, set<string> > G;
int n;

int dfs(string u, set<string> &vis) {
  int ans = 1;
  if (vis.count(u) > 0)
    return 0;
  
  vis.insert(u);  
  
  for (set<string>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    ans = max(ans, dfs(*it, vis) + 1);
  }
  
  return ans;
}

string tolower(string u) {
  string ans = "";
  for (int i = 0; i < (int) u.size(); i++) {
    ans.push_back(u[i] + ((u[i] >= 'A' && u[i] <= 'Z') ? 32 : 0));
  }
  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    char u[32], v[32];
    scanf(" %s reposted %s ", u, v);
    G[tolower(v)].insert(tolower(u));
  }

  set<string> vis;
  printf("%d\n", dfs("polycarp", vis));
  
  return 0;
}
