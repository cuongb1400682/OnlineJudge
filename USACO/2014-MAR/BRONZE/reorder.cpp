#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int cow[100];
int pos[101];
int N;

int shifting(int i) {
	int j;
	int retval = 0;
	i = cow[i];
	int end = i;

	do {
		j = pos[i];
		swap<int>(i, cow[j]);
		++retval;
	} while (i != end);

	return retval;
}

int main(void) {
	freopen("reorder.in", "r", stdin);
	freopen("reorder.out", "w", stdout);

	cin >> N;

	for (int i = 0; i < N; ++i)
		cin >> cow[i];

	for (int i = 0, _cow; i < N; ++i) {
		cin >> _cow;
		pos[_cow] = i;
	}

	int n_cyclic = 0;
	int max_shift = -1;
	for (int i = 0; i < N; ++i)
		if (pos[cow[i]] != i) {
			++n_cyclic;
			max_shift = max<int>(max_shift, shifting(i));
		}

	cout << n_cyclic << " " << max_shift;

	return 0;
}
