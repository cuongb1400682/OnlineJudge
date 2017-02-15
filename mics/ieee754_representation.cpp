#include <stdio.h>
#include <string>
#include <algorithm>
using namespace std;

string to_bin(unsigned char x) {
	string ans = "";
	while (x > 0) {
		ans.push_back("01"[x & 1]);
		x >>= 1;
	}
	reverse(ans.begin(), ans.end());
	while (ans.size() < 8)
		ans = string("0") + ans;
	return ans;
}

string f2s(float x) {
	int sign;
	if (x < 0) {
		sign = -1;
		x = -x;
	}
	unsigned char *p = (unsigned char *) (&x);
	string ans = "";
	for (int i = 0; i < 4; i++)
		ans = to_bin(p[i]) + ans;
	if (sign < 0)
		ans[0] = '1';
	return ans;
}

int main() {
	float x;
	while (true) {
		scanf("%f", &x);
		printf("%s\n", f2s(x).c_str());		
	}
}
