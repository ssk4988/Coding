#include <bits/stdc++.h>
using namespace std;

// try all strings that match the pattern with backtracking
// since there are at most 4 _ chars, then there are 26^4
// strings at most
bool query(int i, string& s, vector<bool>& legal, set<string>& dict) {
	if (i == s.length()) 
		return dict.count(s);

	if (s[i] != '_')
		return query(i + 1, s, legal, dict);

	for (int j = 0; j < 26; j++) 
		if (legal[j]) {
			s[i] = 'a' + j;

			if (query(i + 1, s, legal, dict))
				return true;
		}

	s[i] = '_';
	return false;
}

void solve() {   
	string category;
	cin >> category;

	int n;
	cin >> n;

	set<string> dict;

	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		dict.insert(s);
	}

	int q;
	cin >> q;

	for (int i = 0; i < q; i++) {
		string s;
		cin >> s;

		vector<bool> legal(26, 1);
		for (char c : s)
			if (isalpha(c))
				legal[c - 'a'] = 0;

		if (query(0, s, legal, dict))
			cout << "No cheaters here!\n";
		else
			cout << "That's not a word for a(n) " << category << "!\n";
	}
} 

int main() {
	int t; cin >> t; 
	while (t--) solve();

	return 0;
}
