#include <iostream>
#include <fstream>

using namespace std;

const int MAX_N = 1000;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
const int navigate[2][4] = {{3, 2, 1, 0}, {1, 0, 3, 2}};

int mirrors[MAX_N][MAX_N];
int n, m;

inline int direct(int x, int y) {
    if (x == -1 && y == 0)
        return 2;
    else if (x == 0 && y == 1)
        return 3;
    else if (x == 1 && y == 0)
        return 0;
    else
        return 1;
}

int reflect(int x, int y, int direction) {
    int retval = 1;

    while (true) {
        int next = navigate[mirrors[x][y]][direction];
        direction = direct(dx[next], dy[next]);
        x += dx[next];
        y += dy[next];

        if (x < 0 || x >= n || y < 0 || y >= m)
            break;

        ++retval;
    }

    return retval;
}

int max_reflection() {
    int retval = -1, nreflect;

    for (int i = 0; i < m; ++i) {
        nreflect = max(reflect(0, i, 0), reflect(n - 1, i, 2));

        if (nreflect > retval)
            retval = nreflect;
    }

    for (int i = 0; i < n; ++i) {
        nreflect = max(reflect(i, 0, 3), reflect(i, m - 1, 1));

        if (nreflect > retval)
            retval = nreflect;
    }

    return retval;
}

int main(void) {
    ifstream in("mirror.in");
    in >> n >> m;
    char ch;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            in >> ch;
            if (ch == '/')
                mirrors[i][j] = 0;
            else
                mirrors[i][j] = 1;
        }
    in.close();

    ofstream out("mirror.out");
    out << max_reflection();
    out.close();

    return 0;
}
