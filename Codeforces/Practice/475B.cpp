#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;

int n, m, lab[512], m_lab[512], label, n_component;
bool on_stk[512];
vector<int> G[512];
stack<int> stk;

void init() {
  char hline[32], vline[32];
  int label, lab[32][32];
  
  scanf("%d %d", &n, &m);
  scanf(" %s %s ", hline, vline);

  label = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      lab[i][j] = label++;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      int u, v;

      u = lab[i][j];

      if (hline[i] == '>')
        v = (j + 1 < m ? lab[i][j + 1] : -1);
      else
        v = (j > 0 ? lab[i][j - 1] : -1);

      if (v >= 0) G[u].push_back(v);

      if (vline[j] == 'v')
        v = (i + 1 < n ? lab[i + 1][j] : -1);
      else
        v = (i > 0 ? lab[i - 1][j] : -1);
      
      if (v >= 0) G[u].push_back(v);
    }
}

void tarjan(int u) {
  m_lab[u] = lab[u] = ++label;
  stk.push(u); on_stk[u] = true;

  for (vector<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    int v = *it;
    if (lab[v] == 0) {
      tarjan(v);
      m_lab[u] = min(m_lab[u], m_lab[v]);
    } else if (on_stk[v]) {
      m_lab[u] = min(m_lab[u], lab[v]);
    }
  }

  if (m_lab[u] == lab[u]) {
    ++n_component;
    while (stk.top() != u) {
      on_stk[stk.top()] = false;
      stk.pop();
    }
    on_stk[stk.top()] = false;
    stk.pop();
  }
}

int main() {
  init();
  tarjan(0);
  puts(n_component == 1 && label == n * m ? "YES" : "NO");    
  return 0;
}
