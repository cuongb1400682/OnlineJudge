#include <stdio.h>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <stdlib.h>
#include <algorithm>
 
using namespace std;
 
const bool is_prime[] = {
  0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0
};
 
vector<int> s, t;
 
vector<int> move_back(vector<int> s, int first, int last) {
  if (first < last) {
    for (int i = first; i < last; i++)
      swap(s[i], s[i + 1]);
  } else {
    for (int i = first; i > last + 1; i--)
      swap(s[i], s[i - 1]);
  }
  return s;
}
 
vector<int> move_front(vector<int> s, int first, int last) {
  if (first < last) {
    for (int i = first; i < last - 1; i++)
      swap(s[i], s[i + 1]);
  } else {
    for (int i = first; i > last; i--)
      swap(s[i], s[i - 1]);
  }
  return s;  
}
 
void next_config(vector<int> s,
         vector<vector<int> > &ans) {
  vector<int> neg, pos, t;
  int p_num, n_num, small_pos, large_pos;
  ans.clear();
  for (int i = 0; i < 8; i++)
    if (s[i] < 0)
      neg.push_back(i);
    else
      pos.push_back(i);
  for (int i = 0; i < (int) neg.size(); i++) {
    for (int j = 0; j < (int) pos.size(); j++) {
      p_num = s[pos[j]];
      n_num = -s[neg[i]];
      if (is_prime[p_num + n_num]) {
    small_pos = (p_num > n_num ? neg[i] : pos[j]);
    large_pos = (p_num > n_num ? pos[j] : neg[i]);
    ans.push_back(move_back(s, large_pos, small_pos));
    ans.push_back(move_front(s, small_pos, large_pos));
      }
    }
  }
}
 
void print(string cmt, vector<int> a) {
  printf("%s: ", cmt.c_str());
  for (int i = 0; i < 8; i++)
    printf("%3d", a[i]);
  printf("\n");
}
 
int bfs() {
  set<vector<int> > visited;
  queue <pair<vector<int>, int> > q;
  vector<vector<int> > a;
  vector<vector<int> >::iterator it;
  vector<int> u;
  int l;  
 
  q.push(make_pair(s, 0));
  visited.insert(s);
 
  while (!q.empty()) {
    u = q.front().first;
    l = q.front().second;
    q.pop();
    if (u == t)
      return l;
    next_config(u, a);
    for (it = a.begin(); it != a.end(); it++) {
      if (visited.count(*it) == 0) {
    q.push(make_pair(*it, l + 1));
    visited.insert(*it);
      }
    }
  }
 
  return -1;
}
 
bool cmp(int a, int b) {
  return abs(a) < abs(b);
}
 
int main() {
  int T, no = 1, a[8];
  scanf("%d", &T);
  while (T--) {
    for (int i = 0; i < 8; i++)
      scanf("%d", &a[i]);
    s = vector<int>(a, a + 8);
    sort(a, a + 8, cmp);
    t = vector<int>(a, a + 8);
    printf("Case %d: %d\n", no++, bfs());
  }
  return 0;
}
 
