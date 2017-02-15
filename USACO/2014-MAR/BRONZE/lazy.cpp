#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_N = static_cast<int>(1e5);
const int MAX_X = static_cast<int>(1e6);

int N, K;
int buf[MAX_X+3];
vector<int> point;

int main(void) {
	freopen("lazy.in", "r", stdin);
	freopen("lazy.out", "w", stdout);

	int limit = -1;
	int * x = buf - 1;

	cin >> N >> K;

	for (int i = 0, coor, grass; i < N; ++i) {
		cin >> grass >> coor;
		x[coor] = grass;
		point.push_back(coor);
		limit = max<int>(limit, coor + K);
	}

	point.push_back(-1);
	point.push_back(MAX_X+1);
	sort(point.begin(), point.end());

	for (size_t i = 1; i <= point.size() - 1; ++i)
		x[point[i]] += (i > 0) ? x[point[i - 1]] : 0;
	x[-1] = 0;

	vector<int>::iterator left_it, right_it;
	int result = -1;

	for (int i = 0, left, right; i <= limit; ++i) {
		left = (i > K) ? i - K : 0;
		right = (i + K <= MAX_X) ? i + K : MAX_X;

		left_it = lower_bound(point.begin(), point.end(), left);
		left_it--;

		right_it = lower_bound(point.begin(), point.end(), right);
		if (*right_it - i > K)
			right_it--;

		result = max<int>(result, x[*right_it] - x[*left_it]);
	}

	cout << result;
	return 0;
}
