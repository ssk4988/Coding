#include <bits/stdc++.h>
using namespace std;

#include <tr2/dynamic_bitset>
using namespace tr2;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
const int B = 1e5+10;
using bs = bitset<B>;
bs left2, right2, move2, onleft, onright;
void solve() {
    string s; cin >> s;
    int x = 0;
    int n = sz(s);
    rep(i, 0, n) {
        if(s[i] == 'X') {
            x = i;
        }
    }
    left2[x] = right2[x] = move2[x] = 1;
    rep(i, 0, x) {
        onleft[i] = s[i] == '#';
    }
    rep(i, x+1, n) onright[i] = s[i] == '#';
    bool reachend = false;
    rep(t, 0, n) {
        auto new_left = (right2 | move2) & ~(onright >> (t+1));
        auto new_right = (left2 | move2) & ~(onleft << (t+1));
        auto new_move = ((left2 | right2) << 1) & ~((onright >> t) | (onright >> (t+1)));
        left2 = new_left;
        right2 = new_right;
        move2 = new_move;
        if(left2[n] || right2[n] || move2[n]) reachend = true;
    }
    cout << (reachend || left2.any() || right2.any() || move2.any() ? "Yes" : "No") << "\n";
    onleft.reset();
    onright.reset();
    left2.reset();
    right2.reset();
    move2.reset();

}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }

    return 0;
}
