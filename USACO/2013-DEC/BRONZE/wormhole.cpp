#include <fstream>
#include <vector>

using namespace std;

const int N_MAX = 12;

vector<int> ls; // list of pair of point (ls[i]; partner[ls[i]])
int x[N_MAX + 1];
int y[N_MAX + 1];
int partner[N_MAX + 1];
int n;
int result;

void sort_point() {
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = i + 1; j <= n; ++j)
            if ((y[i] > y[j]) || (y[i] == y[j] && x[i] > x[j])) {
                int t = x[i];
                x[i] = x[j];
                x[j] = t;

                t = y[i];
                y[i] = y[j];
                y[j] = t;
            }
    }
}

bool cycle_exist() {
    // parent[i] is the point visited before i
    int parent[N_MAX + 1];
    int i;
    int j;
    int k;

    // for each point (x[i]; y[i])
    for (i = 1; i <= n; ++i) {
        // because we can't go from negative position (x > 0),
        // we must skip the point that has x = 0
        if (x[i] == 0) continue;

        // use k alternative to i (i is used for the for-loop)
        k = i;

        // initialize the parent[] array
        for (j = 0; j <= N_MAX; ++j) parent[j] = 0;

        // the first point (the point we are working) has no parent
        parent[i] = -1;

        // with point (x[k]; y[k]), we go 2 times:
        //     1) from k to partner of k
        //     2) from partner of k to the right (+X) point of it

        // while (true) { ... } is an infinite loop,
        // so the condition to break it is when we go to
        // point B from point A (A can be the partner or the left point of B)
        // and we can determine that A is parent of B,
        // that means we have a CYCLE
        while (true) {
            // go to the partner of k
            j = partner[k];
            // if j is parent of k
            if (parent[j] == k)
                return true;
            // if not make j is parent of k
            parent[j] = k;

            // go to the right point
            if (y[j + 1] == y[j]) {
                k = j + 1;
                if (parent[k] == j)
                    return true;
                parent[k] = j;
            } else
                 break;
        }
    }

    return false;
}

// get unused point to make pair
int get_unused(int start) {
    int j;
    // begin from "start" point to the end, looking for which point has no partner
    for (j = start; (j < n) && (partner[j] != 0); ++j)
        ;
    return j;
}

void list_point(int i) {
    if (i >= n / 2) {
        result += cycle_exist();
        return;
    }

    ls.push_back(get_unused(1));

    for (int j = ls[i] + 1; j <= n; ++j)
        if (partner[j] == 0) {
            partner[j] = ls[i];
            partner[ls[i]] = j;

            list_point(i + 1);

            partner[j] = 0;
            partner[ls[i]] = 0;
        }

    ls.pop_back();
}

int solve() {
    sort_point();
    list_point(0);
    return result;
}

int main(void) {
    ifstream in("wormhole.in");
    in >> n;
    for (int i = 1; i <= n; ++i)
        in >> x[i] >> y[i];
    in.close();

    ofstream out("wormhole.out");
    out << solve();
    out.close();

    return 0;
}
