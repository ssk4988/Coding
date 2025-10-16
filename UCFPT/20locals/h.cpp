#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int k, s, e; cin >> k >> s >> e;
    s--, e--;
    vii moves;
    vi cleared;
    for(int on = k-1, i = 1, start = 0; on >= 1; start += on, on--, i++) {
        for(int j = k-1; j >= i; j--) {
            moves.emplace_back(0, j);
        }
        rep(j, i+1, k) {
            moves.emplace_back(j, i);
        }
    }
    cleared.push_back(0);
    for(int start = k * (k-1)/2 - 3, i = k-2, on = 2; on < k; on++, start -= on, i--) {
        for(int t : cleared) {
            moves.emplace_back(i, t);
        }
        cleared.push_back(i);
        reverse(all(cleared));
        for(int t : cleared) {
            moves.emplace_back(t, k-1);
        }
        reverse(all(cleared));
    }
    assert(sz(moves) <= (k-1) * (k-1) * 2);
    vi rl(k);
    rl[0] = s;
    rl[k-1] = e;
    int cur = 1;
    rep(i, 0, k) {
        if(i == s || i == e) continue;
        rl[cur++] = i;
    }
    cout << sz(moves) << "\n";
    for(auto [i, j] : moves) {
        cout << rl[i]+1 << " " << rl[j]+1 << "\n";
    }

    return 0;
}
