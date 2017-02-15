#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, int> names;
int combos[1000][4];
int nnames;
int ncombos;

void sort_combo(int combo[3]) {
    for (int i = 0; i <= 1; ++i)
        for (int j = i + 1; j <= 2; ++j)
            if (combo[i] > combo[j]) {
                int t = combo[i];
                combo[i] = combo[j];
                combo[j] = t;
            }
}

int* find_combo(int combo[3]) {
    for (int i = 0; i < ncombos; ++i) {
        if (combo[0] == combos[i][0] && combo[1] == combos[i][1] && combo[2] == combos[i][2])
            return combos[i];
    }

    return (int *)0;
}

int main() {
    int n;
    int combo[3] = {0};
    int result = 0;
    string s;

    ifstream in("records.in");
    in >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            in >> s;
            if (names.find(s) == names.end()) {
                nnames++;
                names.insert(std::make_pair<string, int>(s, nnames));
                combo[j] = nnames;
            } else {
                combo[j] = names[s];
            }
        }

        sort_combo(combo);
        int *p = find_combo(combo);
        if (p == 0) {
            for (int j = 0; j < 3; ++j)
                combos[ncombos][j] = combo[j];

            combos[ncombos][3] = 1;
            if (result < 1)
                result = 1;
            ++ncombos;
        } else {
            p[3]++;
            if (result < p[3])
                result = p[3];
        }

    }
    in.close();

    ofstream out("records.out");
    out << result;
    out.close();

    return 0;
}
