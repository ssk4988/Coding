#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

const int B = 50050;
using bs = bitset<B>;

bs ans, b, tog;
vector<bs> bit;

void solve() {
    int n; cin >> n;
    vi a(n);
    vi pref{0};
    rep(i, 0, n) {
        char c; cin >> c; a[i] = c == '1';
        pref.push_back(pref.back() + (a[i] ? 1 : -1));
    }
    string bstr; cin >> bstr;
    rep(i, 0, n) {
        b[i+1] = bstr[i] == '1';
    }
    map<int, vi> buckets;
    rep(i, 0, n+1) {
        buckets[pref[i]].push_back(i);
    }
    vi suffcarry(n+1, 1);
    for(auto &[p, idxs] : buckets | views::reverse) {
        for(int i : idxs) {
            tog[n-i].flip();
        }
        for(int i : idxs) {
            if(i == 0) continue;
            ans &= ((tog ^ bit[b[i]]) << (n-i)) | (bit[1] << i);
            int endbit = tog[n] ^ b[i];
            if(endbit == 0) ans &= ~(bit[1] << i);
        }
    }
    rep(i, 1, n+1) {
        cout << ans[i];
    }
    cout << "\n";



    // reset for next test case
    rep(i, 0, n+1) {
        ans[i] = 1;
        tog[i] = 0;
    }

}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    bit.resize(2);
    rep(i, 0, B) {
        bit[0][i] = 0;
        bit[1][i] = 1;
        ans[i] = 1;
    }
    int n; cin >> n;
    rep(i, 0, n) solve();

    return 0;
}
