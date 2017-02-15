#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stack>

using namespace std;

#define SZ 128

int n;
char authors[SZ][SZ];
bool a[26][26];

void init() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf(" %s ", authors[i]);
}

bool build_graph() {
  int max_len, k, len_au_i, len_au_j;
  memset(a, false, sizeof(a));
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      len_au_i = strlen(authors[i]);
      len_au_j = strlen(authors[j]);
      max_len = min(len_au_i, len_au_j);
      for (k = 0; k < max_len; k++)
        if (authors[i][k] != authors[j][k]) {
          a[authors[j][k] - 'a'][authors[i][k] - 'a'] = true;
          break;
        }
      if (k == max_len && len_au_i > len_au_j)
        return false;
    }
  }
  return true;
}

void tarjan(int u, int *lab, int *min_lab, int &n_label,
            stack<int> &stk, bool *on_stack, bool *vis) {
  lab[u] = min_lab[u] = ++n_label;
  stk.push(u); on_stack[u] = true;
  vis[u] = true;
  for (int v = 0; v < 26; v++) {
    if (a[u][v]) {
      if (lab[v] == 0) {
        tarjan(v, lab, min_lab, n_label, stk, on_stack, vis);
        lab[u] = min(lab[u], min_lab[v]);
      } else if (on_stack[v]) {
        lab[u] = min(lab[u], lab[v]);
        throw NULL;
      }
    }
  }

  if (lab[u] == min_lab[u]) {
    while (stk.top() != u) {
      on_stack[stk.top()] = false;
      stk.pop();
    }
    on_stack[stk.top()] = false;
    stk.pop();
  }
}

bool is_dag() {
  bool vis[26] = {false};
  for (int u = 0; u < 26; u++) {
    if (vis[u]) continue;
    try {
      bool on_stack[26] = {false};
      int lab[26] = {0}, min_lab[26] = {0}, n_label = 0;
      stack<int> stk;
      
      tarjan(u, lab, min_lab, n_label, stk, on_stack, vis);
    } catch (...) {
      return false;
    }
  }
  return true;
}

void topo_sort(int u, bool *vis, string &ans) {
  if (vis[u])
    return;
  vis[u] = true;
  for (int v = 0; v < 26; v++)
    if (a[u][v])
      topo_sort(v, vis, ans);
  ans.push_back(u + 'a');
}

int main() {
  init();
  if (!build_graph() || !is_dag())
    puts("Impossible");
  else {
    string ans = "";
    bool vis[26] = {false};
    for (int u = 0; u < 26; u++)
      if (!vis[u])
        topo_sort(u, vis, ans);
    puts(ans.c_str());
  }
  return 0;
}
