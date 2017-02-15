#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

using namespace std;

const int MAX_N = 1000;
const int MAX_C = 100;

vector<int> height;
int level[MAX_N];
int n;
int result;

void sort(int i, int j, vector<int> & a) {
    if (i >= j) return;

    int low = i;
    int high = j;
    int p = height[(i + j) / 2];

    do {
        while (p > a[i]) ++i;
        while (p < a[j]) --j;

        if (i <= j) {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;

            ++i;
            --j;
        }
    } while (i <= j);

    sort(low, j, a);
    sort(i, high, a);
}

int main() {
    ifstream in("skidesign.in");
    in >> n;
    for (int i = 0, h; i < n; ++i) {
        in >> h;
        height.push_back(h);
    }
    in.close();

    sort(0, height.size() - 1, height);

    int start = -1;
    for (int i = 0; i < n; ++i)
        if (height[i] > 17) {
            level[i] = height[i] - 17;
            if (start == -1)
                start = i;
        }

    result = numeric_limits<int>::max();
    int tmp;
    for (int i = start; i < n; ++i) {
        tmp = 0;
        for (int j = 0; j < i && height[j] < level[i]; ++j)
            tmp += (level[i] - height[j]) * (level[i] - height[j]);

        for (int j = n - 1; j > i; --j)
            tmp += (level[i] - level[j]) * (level[i] - level[j]);

        if (result > tmp)
            result = tmp;
    }

    ofstream out("skidesign.out");
    out << result;
    cout << result;
    out.close();
    return 0;
}
