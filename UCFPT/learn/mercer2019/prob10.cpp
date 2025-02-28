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
const int mod = 1e9+7;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vector dp(n+1, vector(10, vi(10)));
        dp[0][0][0] = 1;
        rep(i, 0, n) {
            rep(j, 0, 10) {
                rep(k, 0, 10) {
                    rep(d, 0, 10) {
                        if(i >= 1 && d == j) continue;
                        if(i >= 2 && ((d == j || d == k) || (d > j && j > k) || (d < j && j < k))) continue;
                        (dp[i+1][d][j] += dp[i][j][k]) %= mod;
                    }
                }
            }
        }
        int ans = 0;
        rep(j, 0, 10) {
            rep(k, 0, 10) {
                (ans += dp[n][j][k]) %= mod;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
