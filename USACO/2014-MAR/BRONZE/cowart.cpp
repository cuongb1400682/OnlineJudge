#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <queue>

using namespace std;

/*
 * RED   = 0
 * GREEN = 1
 * BLUE  = 2
 */
const char hu_eye[3] = { 0, 1, 2 };
const char cow_eye[3] = { 0, 0, 1 };
const int hx[4] = { 0, 1, 0, -1 };
const int hy[4] = { 1, 0, -1, 0 };

int N;
int painting[100][100];
bool visited[100][100];

void visit(int x, int y, const char * const see)
{
	queue<pair<int, int> > q;
	q.push(make_pair<int, int>(x, y));
	visited[x][y] = true;

	do {
		int u = q.front().first;
		int v = q.front().second;
		q.pop();

		for (int i = 0; i < 4; ++i) {
			x = u + hx[i];
			y = v + hy[i];
			if (x >= 0 && y >= 0 && x < N && y < N)
				if ((!visited[x][y]) && (see[painting[x][y]] == see[painting[u][v]])) {
					visited[x][y] = true;
					q.push(make_pair<int, int>(x, y));
				}
		}
	} while (!q.empty());
}

int see_painting_by(const char * const see)
{
	int retval = 0;
	memset(visited, false, sizeof(visited));

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (!visited[i][j]) {
				++retval;
				visit(i, j, see);
			}

	return retval;
}

int main(void)
{
	freopen("cowart.in", "r", stdin);
	freopen("cowart.out", "w", stdout);

	cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) {
			char color;
			cin >> color;
			if (color == 'R')
				painting[i][j] = 0;
			else if (color == 'G')
				painting[i][j] = 1;
			else
				painting[i][j] = 2;
		}

	cout << see_painting_by(hu_eye) << " " << see_painting_by(cow_eye);
	return 0;
}
