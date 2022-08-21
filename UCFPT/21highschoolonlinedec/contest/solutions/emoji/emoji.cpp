#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void solve() {
    // Set to hold all previously added letters.
    set<char> added;

    // Retrieve our input string.
    string inp; cin >> inp;

    // For every character
    for (char c : inp) {
        // If set insertion fails, a letter exists twice.
        if (!added.insert(c).second) {
            cout << "Nope\n";
            return;
        }
    }

    // Success!
    cout << "Emote away!\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    rep(i, 0, n)
        solve();

    return 0;    
}
