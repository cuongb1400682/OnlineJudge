#include <math.h>
#include <iostream>
#include <fstream>

using namespace  std;

int a[3]; // FJ
int b[3]; // MASTER
int n;
bool exist[101][101][101];

int begin(int ai) {
    return (ai - 2 <= 0 ? ai - 2 + n : ai - 2);
}

int end(int ai) {
    return (ai + 2 > n ?
                ai + 2 - n :
                ai + 2);
}

int next(int ai) {
    ai++;
    return ai > n ? 1 : ai;
}

int main() {    
    std::ifstream fin("combo.in");

    fin >> n;
    fin >> a[0] >> a[1] >> a[2];
    fin >> b[0] >> b[1] >> b[2];
    fin.close();

    std::ofstream fout("combo.out");
    if (n <= 5) {
        fout << n * n * n;
        return 0;
    }

    int i, j, k;

    int end0 = next(end(a[0]));
    int end1 = next(end(a[1]));
    int end2 = next(end(a[2]));

    for (i = begin(a[0]); i != end0; i = next(i))
        for (j = begin(a[1]); j != end1; j = next(j))
            for (k = begin(a[2]); k != end2; k = next(k)) {
                exist[i][j][k] = true;
            }

    end0 = next(end(b[0]));
    end1 = next(end(b[1]));
    end2 = next(end(b[2]));

    int count = 250;
    for (i = begin(b[0]); i != end0; i = next(i))
        for (j = begin(b[1]); j != end1; j = next(j))
            for (k = begin(b[2]); k != end2; k = next(k))
                if (exist[i][j][k])
                    count--;

    fout << count;
    fout.close();
    return 0;
}
