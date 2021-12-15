#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

map<char, int> keyToOrder = {
	{'C', 0},
	{'D', 1},
	{'E', 2},
	{'F', 3},
	{'G', 4},
	{'A', 5},
	{'B', 6},
};

void wa(int i) { cout << "WA on case " << i << endl; exit(0); }

int main(int argc, char** argv) {
	cin.tie(0)->sync_with_stdio(0);

	ifstream judgeIn(argv[1]);
	ifstream userOut(argv[2]);
	ifstream judgeOut(argv[3]);

	int n; judgeIn >> n;
	for (int i = 1; i <= n; i++) {
		string song; judgeIn >> song;

		string userHands;
		if (!(userOut >> userHands)) {
			cout << "Not enough output" << endl;
			return 0;
		}

		if (sz(userHands) != sz(song))
			wa(i);

		int lastLeft = INT_MIN, lastRight = INT_MAX;
		for (int j = 0; j < sz(song); j++) {
			if (userHands[j] == 'L') {
				if (keyToOrder[song[j]] > lastRight)
					wa(i);
				lastLeft = keyToOrder[song[j]];
			} else if (userHands[j] == 'R') {
				if (keyToOrder[song[j]] < lastLeft)
					wa(i);
				lastRight = keyToOrder[song[j]];
			} else wa(i);
		}
	}
}
