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
        vvi grid(n, vi(n));
        rep(i, 0, n) {
            rep(j, 0, n) cin >> grid[i][j];
        }
        vl row(n), col(n);
        rep(i, 0, n) cin >> row[i];
        rep(i, 0, n) cin >> col[i];
        const ll inf = 1e18;
        ll ans = 0;
        rep(_, 0, 2) {
            vector dp(n+1, vl(2, inf));
            dp[0][0] = 0;
            rep(i, 0, n) {
                rep(j, 0, 2) {
                    rep(k, 0, 2) {
                        bool works = true;
                        rep(l, 0, n) {
                            if(i && grid[i-1][l] + j == grid[i][l] + k) {
                                works = false;
                                break;
                            }
                        }
                        if(works) dp[i+1][k] = min(dp[i+1][k], dp[i][j] + (k ? row[i] : 0));
                    }
                }
            }
            ans += min(dp[n][0], dp[n][1]);
            rep(i, 0, n) {
                rep(j, 0, i) swap(grid[i][j], grid[j][i]);
            }
            swap(row, col);
        }
        if(ans >= inf) ans = -1;
        cout << ans << "\n";
    }
    
    return 0;
}
