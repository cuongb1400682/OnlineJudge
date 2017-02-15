#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

const int MAX_N = 1000;

char words[50000][MAX_N]; // C_STRING
int lable[50000];
int W, N;

void sort_words(int i, int j) {
    if (i >= j)
        return;

    int low = i;
    int high = j;
    int p = lable[(i + j) / 2];

    do {
        while (strcmp(words[p], words[lable[i]]) > 0)
            ++i;
        while (strcmp(words[p], words[lable[j]]) < 0)
            --j;

        if (i <= j) {
            int t = lable[i];
            lable[i] = lable[j];
            lable[j] = t;

            ++i;
            --j;
        }
    } while (i <= j);

    sort_words(low, j);
    sort_words(i, high);
}

int search_word(const char * word, int len) {
    int i = 0;
    int j = W - 1;

    while (i <= j) {
        int mid = (i + j) / 2;
        int r = strncmp(word, words[lable[mid]], len);

        if (r == 0)
            return mid;
        else if (r < 0)
            j = mid - 1;
        else
            i = mid + 1;
    }

    return -1;
}

int main() {
    freopen("auto.in", "r", stdin);
    freopen("auto.out", "w", stdout);

    cin >> W >> N;
    for (int i = 0; i < W; ++i) {
        cin >> words[i];
        lable[i] = i;
    }

    sort_words(0, W - 1);

    char word[1000] = {0};

    for (int i = 0, x; i < N; ++i) {
        cin >> x >> word;
        int word_len = strlen(word);

        int start = search_word(word, word_len);

        if (start >= 0) {
            int am = 1;
            int j;

            for (j = start - 1; j >= 0; --j) {
                int r = strncmp(word, words[lable[j]], word_len);

                if (r == 0)
                    am++;
                else
                    break;
            }

            ++j;

            if (j + x - 1 < W && (strncmp(words[lable[j + x - 1]], word, word_len) == 0))
                cout << lable[j + x - 1] + 1 << endl;
            else
                cout << -1 << endl;
        } else cout << -1 << endl;
    }

    return 0;
}
