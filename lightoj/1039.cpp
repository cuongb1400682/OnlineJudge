#include <stdio.h>
#include <string.h>
#include <queue>

#include <string>

using namespace std;

struct Word {
  unsigned short word;
  int get(int i) {
    return ((word >> 5 * i) & 31);
  }
  int set(int i, char chr) {
    chr -= 'a';
    word &= ~(31 << i * 5);
    word |= (chr << i * 5);
  }
  Word(const char *s = NULL) {
    word = 0;
    if (s == NULL)
      return;
    for (int i = 0; i < 3; i++)
      set(i, s[i]);
  }
  Word(int w) : word(w) {
  }
  Word next(int i, int j) {
    Word ans = *this;
    int at_i = ans.get(i);
    if (j == 0) {
      at_i--;
      if (at_i < 0)
	at_i = 25;
      ans.set(i, at_i + 'a');
    } else {
      at_i = (at_i + 1) % 26;
      ans.set(i, at_i + 'a');
    }
    return ans;
  }
};

Word s, t;
bool is_constraint[27000];
int n;

void add_constraint(const char *_a, const char *_b, const char *_c) {
  for (const char *a = _a; *a; a++)
    for (const char *b = _b; *b; b++)
      for (const char *c = _c; *c; c++) {
	char buf[4] = { *a, *b, *c, '\0' };
	is_constraint[Word(buf).word] = true;
      }
}

int bfs() {
  queue<pair<int, int> > q;
  bool in_queue[27000] = { false };

  if (not is_constraint[s.word]) {
    q.push(make_pair(s.word, 0));
    in_queue[s.word] = true;
  }

  while (not q.empty()) {
    int x = q.front().first;
    int l = q.front().second;
    q.pop();

    if (x == t.word)
      return l;

    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 2; j++) {
	Word w = Word(x).next(i, j);
	if (not in_queue[w.word] and not is_constraint[w.word]) {
	  q.push(make_pair(w.word, l + 1));
	  in_queue[w.word] = true;
	}
      }
  }

  return -1;
}

int main() {
  int no = 1, T;
  char a[256], b[256], c[256];
  
  scanf("%d", &T);
  while (T--) {
    scanf(" %s ", a); s = Word(a);
    scanf(" %s ", a); t = Word(a);
    scanf("%d", &n);
    memset(is_constraint, false, sizeof(is_constraint));
    for (int i = 0; i < n; i++) {
      scanf(" %s %s %s ", a, b, c);
      add_constraint(a, b, c);
    }
    printf("Case %d: %d\n", no++, bfs());
  }
  return 0;
}
