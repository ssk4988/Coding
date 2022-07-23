#include <bits/stdc++.h>
using namespace std;

// O(n) solution to snow

void solve() {   
	int n;
	cin >> n;

	vector<int> h(n);
	for (int& x : h) cin >> x;

	string s; 
	cin >> s;

	// store where snowmen of each height are located at
	vector<vector<int>> pos(n + 1);

	for (int i = n - 1; i >= 0; i--)
		pos[h[i]].push_back(i);
	
	// circular linked list pointers
	vector<int> l(n), r(n);

	for (int i = 0; i < n; i++) {
		l[i] = (i - 1 + n) % n;
		r[i] = (i + 1) % n;
	}

	int ptr = n; // current biggest height
	vector<bool> dead(n); // is this index dead
	int numAlive = n;

	// get the largest snowman with the smallest index
	auto getBiggest = [&]() {
		while (true) {
			while (pos[ptr].size() == 0) ptr--;
			
			int x = pos[ptr].back();
			pos[ptr].pop_back();

			if (!dead[x])
				return x;
		}
	};

	// remove the snowman at index i
	auto remove = [&](int i) {
		dead[i] = 1;
		numAlive--;

		r[l[i]] = r[i];
		l[r[i]] = l[i];
		l[i] = r[i] = -1;
	};

	int ans = 0;

	while (numAlive > 0) {
		int i = getBiggest();

		int at = i;
		for (int j = 0; j < h[i] && numAlive > 0; j++) {
			int next = s[ans] == 'L' ? l[at] : r[at];

			remove(at);

			at = next;
		}

		ans++;
	}

	cout << ans << "\n";
} 

int main() {
	int t; cin >> t; 
	while (t--) solve();

	return 0;
}
