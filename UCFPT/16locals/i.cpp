#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
const int mod = 1e9+7;
const int inv2 = (mod+1)/2;
const int N = 16;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi s(n), t(n);
        rep(i, 0, n) {
            cin >> s[i] >> t[i];
            s[i]--, t[i]--;
        }
        vector dp(1 << n, vector(n, vi(4, -1)));
        int allmask = (1 << n)-1;
        auto go = [&](int mask, int last, int avail, auto &&go) -> int {
            if(avail == 0) return 0;
            if(mask == allmask) return 1;
            auto &ans = dp[mask][last][avail];
            if(ans != -1) return ans;
            ans = 0;
            rep(i, 0, n) {
                if((mask >> i)&1) continue;
                int avail1 = 0;
                rep(flip, 0, 2) {
                    int l = flip ? t[i] : s[i];
                    int r = flip ? s[i] : t[i];
                    bool works = false;
                    rep(bit, 0, 2) {
                        if(((avail >> bit)&1) == 0) continue;
                        int v = bit ? s[last] : t[last];
                        if(v == l) works = true;
                    }
                    if(works) avail1 |= 1 << flip;
                }
                (ans += go(mask ^ (1 << i), i, avail1, go)) %= mod;
            }
            return ans;
        };
        int ans = 0;
        rep(i, 0, n) {
            (ans += go(1 << i, i, 3, go)) %= mod;
        }
        cout << ans << "\n";
        // cout << (2*go(0, 0, 0, 1, go))%mod << "\n";
    }

    return 0;
}
// ab|bc|cd
// ba|cb|dc
// a=c, b=d
