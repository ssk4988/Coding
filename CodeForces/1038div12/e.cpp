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
const ll mod = 998244353;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        vvi a(2, vi(n));
        rep(i, 0, 2) {
            rep(j, 0, n) {
                cin >> a[i][j];
            }
        }
        int tl = a[0][0], br = a[1][n-1];
        ll base = 1;
        if(tl == -1) {
            (base *= k) %= mod;
        }
        if(br == -1) {
            (base *= k) %= mod;
        }
        if(n == 1) {
            cout << base << "\n";
            continue;
        }
        {
            vvi b(2, vi(n-1));
            rep(i, 1, n) {
                b[0][i-1] = a[0][i];
                b[1][i-1] = a[1][i-1];
            }
            a = b;
            n--;
        }
        // delta is row1 - row0
        vvi delta(n, vi(k*2+10));
        const int O = k+2;
        rep(i, 0, n) {
            rep(c, 1, k+1) {
                if(a[0][i] != -1 && c != a[0][i]) continue;
                rep(d, 1, k+1) {
                    if(a[1][i] != -1 && d != a[1][i]) continue;
                    delta[i][d-c+O]++;
                }
            }
        }
        const int inf = 1e9;
        vl pdp(k+2, 1);
        for(int i = n-1; i >= 0; i--) {
            vl dp(k+2);
            // row 1 > row 0
            rep(cur, 0, k+2) {
                rep(d, 1, k+1) {
                    (dp[cur] += delta[i][d+O] * pdp[d]) %= mod;
                }
            }
            // rep(cur, 0, k+2) {
            //     (dp[cur] += delta[i][0+O] * pdp[cur]) %= mod;
            // }
            // row 1 <= row 0
            rep(cur, 0, k+2) {
                rep(d, 0, k+1) {
                    if(cur <= k && d > cur) continue;
                    (dp[cur] += delta[i][O-d] * pdp[cur > k ? cur : cur-d]) %= mod;
                }
            }
            swap(pdp, dp);
        }
        ll ans = pdp[k+1];
        (ans *= base) %= mod;
        (ans += mod) %= mod;
        cout << ans << "\n";
    }
    
    return 0;
}
