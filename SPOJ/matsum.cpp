#include <stdio.h>
#include <string.h>

#define SZ 2048

struct bit_t {
  void create(int n) {
    this->n = n;
    memset(b, 0, sizeof(b));
  }
  void update(int x, int value) {
    for (; x <= n; x += (x & -x)) {
      b[x] += value;
    }
  }
  int query(int x) {
    int ans = 0;
    for (; x > 0; x -= (x & -x))
      ans += b[x];
    return ans;
  }
  int query(int x, int y) {
    return query(y) - (x > 0 ? query(x - 1) : 0);
  }
  int b[SZ];
  int n;
};

struct bit2d_t {
  void create(int n) {
    this->n = n;
    for (int i = 1; i <= n; i++)
      b[i].create(n);
  }
  void update(int x, int y, int value) {
    for (; x <= n; x += (x & -x))
      b[x].update(y, value);
  }
  int query(int x, int y) {
    int ans = 0;
    if (x <= 0 || y <= 0)
      return 0;
    for (; x > 0; x -= (x & -x))
      ans += b[x].query(y);
    return ans;
  }
  int query(int x1, int y1, int x2, int y2) {
    x1--;
    y1--;
    return query(x2, y2) - query(x2, y1) -
      query(x1, y2) + query(x1, y1);
  }
  int n;
  bit_t b[SZ];
};

bit2d_t a;

int main(void) {
  char type[64];
  int x, y, sum, x1, x2, y1, y2, t, n, num;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    a.create(n);
    while (1) {			
      scanf("%s", type);
      if (type[0] == 'E') {
	break;
      } else if (type[1] == 'E') {
	scanf("%d %d %d", &x, &y, &num);
	x++, y++;
	num -= a.query(x, y, x, y);
	a.update(x, y, num);
      } else {
				
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	x1++, y1++, x2++, y2++;
	printf("%d\n", a.query(x1, y1, x2, y2));
      }
    }
    printf("\n");
  } 
  return 0;
}
