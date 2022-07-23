#include <bits/stdc++.h>
using namespace std;

random_device rd;

int main() {
	srand(rd());

	int h, w; cin >> h >> w;
	vector<vector<int>> a(h+2,vector<int>(w+2));
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (rand() & 1) continue;
			for (int di = 0; di < 3; di++) {
				for (int dj = 0; dj < 3; dj++) {
					a[i+di][j+dj]++;
				}
			}
		}
	}

	int bad_clues; cin >> bad_clues;
	while (bad_clues--) {
		int i = rand() % (h+2), j = rand() % (w+2);
		int diff = rand() & 1 ? 1 : -1;
		if (a[i][j] == 0) diff = 1;
		if (a[i][j] == 9) diff = -1;
		a[i][j] += diff;
	}

	cout << h << " " << w << endl;
	for (int i = 0; i < h+2; i++) {
		for (int j = 0; j < w+2; j++) {
			cout << a[i][j] << " \n"[j==w+1];
		}
	}
}
