#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    int n;
    vector<int> a;

    ifstream in("baseball.in");
    in >> n;
    for (int i = 0, tmp; i < n; ++i) {
        in >> tmp;
        a.push_back(tmp);
    }
    in.close();

    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1, tmp; j < n; ++j)
            if (a[i] > a[j]) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }

    int count = 0;
    float x, y, z;
    for (int i = 0; i < n - 2; ++i)
        for (int j = i + 1; j < n - 1; ++j)
            for (int k = j + 1; k < n; ++k) {
                x = a[i];
                y = a[j];
                z = a[k];
                if ((z - y) / (y - x) > 2.)
                    break;
                else if ((z - y) / (y - x) >= 1.) {
                    ++count;
                }
            }

    ofstream out("baseball.out");
    out << count;
    out.close();
    return 0;
}
