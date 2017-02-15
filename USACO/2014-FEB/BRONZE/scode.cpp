#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long int uint64;

string original;
vector<string> substrs;
vector<int> sorted_order;
vector<uint64> count_ways;

int compare(int i, int j) {
	return substrs[i].size() > substrs[j].size();
}

int count_letters(string s) {
	bool has[256] = { false };
	int retval = 0;

	for (string::iterator ch = s.begin(); ch != s.end(); ch++)
		if (!has[*ch]) {
			has[*ch] = true;
			++retval;
		}

	return retval;
}

void list_all_substring() {
	int nletter = count_letters(original);
	int org_len = original.size();
	string tmp;

	for (int i = nletter + (nletter == 1); i <= org_len / 2 + 1; ++i) {
		for (int j = 0; j <= org_len - i; ++j) {
			tmp = original.substr(j, i);
			if (count_letters(tmp) == nletter && (find(substrs.begin(), substrs.end(), tmp) == substrs.end())) {
				substrs.push_back(tmp);
			}
		}
	}

	for (size_t i = 0; i < substrs.size(); ++i)
		sorted_order.push_back(i);

	count_ways.assign(substrs.size(), 0);
	sort(substrs.begin(), substrs.end());
	sort(sorted_order.begin(), sorted_order.end(), compare);
}

uint64 the_number_of_ways(string str) {
	if (str.size() < 2)
		return 0;
	if (str == original)
		return 1;

	vector<string>::iterator pos = find(substrs.begin(), substrs.end(), str);
	int x = pos - substrs.begin();

	if (pos == substrs.end())
		return 0;
	else if (count_ways[x] > 0)
		return count_ways[x];

	string tmp;
	count_ways[x] = 0;

	tmp = str.substr(0, str.size() - 1);
	count_ways[x] += the_number_of_ways(str + tmp);
	count_ways[x] += the_number_of_ways(tmp + str);

	tmp = str.substr(1, str.size());
	count_ways[x] += the_number_of_ways(str + tmp);
	count_ways[x] += the_number_of_ways(tmp + str);

	return count_ways[x];
}

uint64 solve() {
	uint64 retval = 0;
	if ((original.size() & 1) == 0)
		return 0;

	list_all_substring();

	for (size_t i = 0; i < sorted_order.size(); ++i) {
		retval += the_number_of_ways(substrs[sorted_order[i]]);
	}
	return retval;
}

int main(void) {
	freopen("scode.in", "r", stdin);
	freopen("scode.out", "w", stdout);

	cin >> original;
	cout << solve() << endl;
	return 0;
}
