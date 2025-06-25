#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const int LIM = 1e6+10;
    vector<vl> cnt(4, vl(LIM));
    cnt[0][1] = 1;
    rep(k, 0, 3) {
        rep(i, 1, LIM) {
            for(int j = i; j < LIM; j += i) {
                cnt[k+1][j] += cnt[k][i];
            }
        }
    }
    rep(i, 1, LIM) cnt[3][i] += cnt[3][i-1];
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        ll ans = cnt[3][n];
        for(int sq = 1; sq * sq <= n; sq++) {
            int sq2 = sq * sq;
            ans -= 3 * (n / sq2 - (n/sq2 >= sq));
        }
        for(int tri = 1; tri * tri * tri <= n; tri++) {
            ans--;
        }
        cout << ans/6 << "\n";
    }

    return 0;
}
