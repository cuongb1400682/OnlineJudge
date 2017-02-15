#include <set>
#include <deque>
#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
	int t,n,d;
	scanf("%d", &t);
	for (int no = 1; no <= t; no++) {
		scanf("%d %d", &n, &d);
		deque<int> lst;
		set<int> h;
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			int num;
			scanf("%d", &num);
			if (lst.size() == d) {
				h.erase(lst.front());
				lst.pop_front();
			}
			lst.push_back(num);
			h.insert(num);
			if (lst.size() == d) {
				int mmin = *h.begin();
				int mmax = *h.rbegin();
				ans = max(ans, mmax - mmin);
			} 
		}
		printf("Case %d: %d\n", no, ans);
	}	
}
