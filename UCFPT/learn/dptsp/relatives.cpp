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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vector<vd> c(n, vd(n));
        rep(i, 0, n){
            rep(j, 0, n) cin >> c[i][j];
        }
        const ld oo = 1e9;
        vector<vd> dp(1 << n, vd(n, oo));
        dp[1][0] = 0;
        rep(i, 0, 1 << n){
            rep(j, 0, n){
                if(dp[i][j] == oo) continue;
                rep(k, 0, n){
                    if((i >> k) & 1) continue;
                    dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], c[j][k] + dp[i][j]);
                }
            }
        }
        ld ans = oo;
        rep(i, 0, n){
            ans = min(ans, dp.back()[i] + c[i][0]);
        }
        cout << fixed << setprecision(2) << ans << "\n";
    }
    
    return 0;
}
