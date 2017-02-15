#include <fstream>
#include <iostream>

using namespace std;

const int MAX_C = 10000000;

int skill[12];
int sum[5], n_skill[5];
int result;

void solve(int i) {
    if (i >= 12) {
        int min = sum[1], max = sum[1];
        for (int j = 2; j <= 4; ++j) {
            if (min > sum[j])
                min = sum[j];
            if (max < sum[j])
                max = sum[j];
        }

        if (max - min < result)
            result = max - min;

        return;
    }

    for (int j = 1; j <= 4; ++j)
        if (n_skill[j] < 3) {
            ++n_skill[j];
            sum[j] += skill[i];

            solve(i + 1);

            --n_skill[j];
            sum[j] -= skill[i];
        }
}

int main(void) {
    ifstream in("bteams.in");
    for (int i = 0; i < 12; ++i)
        in >> skill[i];
    in.close();

    result = MAX_C;
    solve(0);

    ofstream out("bteams.out");
    out << result;
    out.close();
    return 0;
}
