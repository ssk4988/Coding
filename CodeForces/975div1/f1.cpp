#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        ll mod; cin >> mod;
        vector dp(n+1, vector(n, vector(n+1, vl(5, -1))));
        // cur val, l, r, stage
        // stages:
        // 0, must expand left without necessarily stopping
        // 1, must expand right without stopping
        // 2, done expanding left and right
        auto go = [&](int v, int l, int r, int stage, auto &&go) -> ll {
            ll &ans = dp[v][l][r][stage];
            if(ans != -1) return ans;
            if(r-l >= v) return ans = 0;
            if(v == n) return ans = l == 0 && r == n && stage == 2;
            ans = 0;
            if(stage == 0) {
                if(l) {
                    ans += (n-v+1) * go(v, l-1, r, stage, go);
                    ans += go(v, l-1, r, 1, go);
                    ans += go(v, l-1, r, 2, go);
                    ans %= mod;
                }
            }
            if(stage == 1) {
                if(r < n) {
                    ans += (n-v+1) * go(v, l, r+1, stage, go);
                    ans += go(v, l, r+1, 2, go);
                    ans %= mod;
                }
            }
            if(stage == 2) {
                rep(s, 0, 3)
                    ans += go(v+1, l, r, s, go);
                ans %= mod;
            }
            return ans;
        };
        ll ans = 0;
        rep(i, 0, n){
            rep(v, 1, n+1) {
                ans += go(v, i, i+1, 1, go);
                ans += go(v, i, i+1, 2, go);
                ans %= mod;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
