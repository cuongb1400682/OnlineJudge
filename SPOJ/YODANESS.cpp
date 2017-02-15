#include <stdio.h>
#include <map>
#include <string>
#include <string.h>
using namespace std;

#define SZ 30005

map<string, int> h;
struct Line { int x, y; } line[SZ];
int bit[SZ], n, t;

int query(int x, int y) {
	int ans = 0;
	if (x > y) swap(x, y);
	for (; y > 0; y -= (y & -y))
		ans += bit[y];
	for (x--; x > 0; x -= (x & -x))
		ans -= bit[x];
	return ans;
}

void update(int x, int value) {
	for (; x <= n; x += (x & -x))
		bit[x] += value;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		h.clear();
		char word[32];
		for (int i = 1; i <= n; i++) {
			scanf("%s", word);
			h[string(word)] = i;
			line[i].x = i;
		}
		for (int i = 1; i <= n; i++) {
			scanf("%s", word);
			line[i].y = h[string(word)];
		}
		memset(bit, 0, sizeof(bit));
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			ans += query(line[i].y, n);
			update(line[i].y, 1);
		}
		printf("%d\n", ans);
	}
	return 0;
}
