#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
int nadj;                 // the number of kinds of adjective in adj[]
vector<string> adj[100];  // Adjectives
vector<string> poem[100]; // poem[i]: attributes of the ith cows
vector<string> result;
bool discovered[100];     // discovered[i]: poem[i] will not be used
int elm[100];             // the number of elements at the ith level in tree

// wheather elm is in container?
bool find(vector<string>::iterator beg, vector<string>::iterator end, string elm) {
    for (vector<string>::iterator i = beg; i != end; ++i)
        if (*i == elm)
            return true;
    return false;
}

void read_file() {
    FILE *f = fopen("nocow.in", "r");
    fscanf(f,"%d%d", &n, &k);

    char s[100] = { 0 };
    // Read n lines
    for (int i = 0; i < n; ++i) {
        // skip the string 'Farmer John has no'
        for (int j = 0; j < 4; ++j)
            fscanf(f, "%s", s);

        // read until meet 'cow.' (EOLINE)
        // With the k-th adjective
        for (int k = 0; ; ++k) {
            fscanf(f, "%s", s);

            if (string(s) == "cow.")
                break;

            poem[i].push_back(string(s));

            // adj[k] must be a list of UNIQUE adjectives
            if (find(adj[k].begin(), adj[k].end(), string(s)) == false)
                adj[k].push_back(s);

            // the final (greatest) value of k is the number of kinds of adjective
            nadj = k + 1;
        }
    }

    // sort the list of adjective with alphabet order
    for (int k = 0; k < nadj; ++k)
        sort(adj[k].begin(), adj[k].end());

    fclose(f);
}

void write_file() {
    FILE *f = fopen("nocow.out", "w");
    for (size_t i = 0; i < result.size() - 1; ++i)
        fprintf(f, "%s ", result[i].data());
    fprintf(f, "%s", result[result.size() - 1].data());
    fclose(f);
}

int main() {
    read_file();

    elm[nadj - 1] = 1; // the lowest elements (leaves) are always 1
    // other greater elements (start with (nadj - 2)-th)
    // the 0-th is greatest
    for (int i = nadj - 2; i >= 0; --i)
        elm[i] = elm[i + 1] * adj[i + 1].size();

    int lv = 0;
    int k_ = k;
    int choose = 0;

    for (;;) {
        int count = elm[lv];

        for (int j = 0; j < n; ++j)
            if (discovered[j] == false)
                if (poem[j][lv] == adj[lv][choose])
                    count--;

        if (k_ > count) {
            k_ -= count;

            for (int j = 0; j < n; ++j)
                if (poem[j][lv] == adj[lv][choose])
                    discovered[j] = true;

            choose++;
        } else {
            result.push_back(adj[lv][choose]);

            for (int j = 0; j < n; ++j)
                if (poem[j][lv] != adj[lv][choose])
                    discovered[j] = true;
            lv++;
            if (lv >= nadj)
                break;
            choose = 0;
        }

        if (k_ <= 0) {
            break;
        }

    }

    write_file();
    return 0;
}
