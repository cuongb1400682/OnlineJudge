#include <stdio.h>
#include <math.h>
#include <string.h>
#include <queue>

using namespace std;

int s, t;
vector<int> prime_list;

void make_prime_list() {
  bool is_prime[2000];
  int sqrt_n = (int) sqrt(1500);

  prime_list.clear();
  memset(is_prime, true, sizeof(is_prime));

  for (int i = 2; i <= sqrt_n; i++) {
    if (not is_prime[i])
      continue;
    for (int j = i * i; j <= 1500; j += i)
      is_prime[j] = false;
  }

  for (int i = 2; i <= 1500; i++)
    if (is_prime[i])
      prime_list.push_back(i);
}

void make_prime_factor_list(int number, vector<int> &v) {
  v.clear();

  int original = number;
  for (int i = 0; number > 1; i++) {
    while (number % prime_list[i] == 0) {
      if (v.empty() or v.back() != prime_list[i])
	v.push_back(prime_list[i]);
      number /= prime_list[i];
    }
  }
  if (not v.empty() && v.back() == original)
    v.pop_back();
}

int bfs() {
  queue<pair<int, int> > q;
  vector<int> v;  
  bool in_queue[1024] = { false };
  int x, y, l;

  q.push(make_pair(s, 0));
  in_queue[s] = true;

  while (not q.empty()) {
    x = q.front().first; l = q.front().second; q.pop();
    if (x == t)
      return l;
    make_prime_factor_list(x, v);
    for (int i = 0; i < (int) v.size(); i++) {
      y = x + v[i];
      if (not in_queue[y] && y <= 1000) {
	q.push(make_pair(y, l + 1));
	in_queue[y] = true;
      }
    }
  }
  
  return -1;
}

int main() {
  int T, no = 1;

  make_prime_list();

  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &s, &t);
    printf("Case %d: %d\n", no++, bfs());
  }
  return 0;
}
