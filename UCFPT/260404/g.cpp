#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        bool neg = k < 0;
        if(neg) k *= -1;
        vi a(n);
        map<int, vi> b;
        rep(i, 0, n) {
            cin >> a[i];
            if(neg) a[i] *= -1;
            int c = a[i];
            a[i] %= k;
            (a[i] += k) %= k;
            b[a[i]].push_back((c - a[i]) / k);
        }
        ll ans = 0;
        for(auto [key, v] : b) {
            sort(all(v));
            ll prv = v[0]-1;
            for(auto x : v) {
                // cerr << x << ",";
                if(x <= prv) {
                    ans += prv+1 - x;
                    x = prv + 1;
                }
                prv = x;
            }
            // cerr << endl;
        }
        cout << ans << "\n";
    }

    return 0;
}
