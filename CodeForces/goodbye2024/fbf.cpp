#include <bits/stdc++.h>
using namespace std;

#define int long long
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


void solve() {
    int n, m, k; cin >> n >> m >> k;
    vvi freq(n, vi(k));
    vi ext(n);
    rep(i, 0, n){
        rep(j, 0, m){
            int v; cin >> v; if(v == -1) ext[i]++;
            else freq[i][v-1]++;
        }
    }
    vvi dp(n, vi(k));
    vi natural(n);
    rep(i, 0, n-1){
        rep(c, 0, k){
            natural[i] += freq[i][c] * freq[i+1][c];
        }
    }
    rep(i, 0, n-1){
        rep(c, 0, k){
            rep(c1, 0, k){
                dp[i+1][c1] = max(dp[i+1][c1], dp[i][c] + ext[i+1] * freq[i][c1] + ext[i] * freq[i+1][c] + (c == c1 ? ext[i] * ext[i+1] : 0));
            }
        }
    }
    ll ans = 0;
    rep(c, 0, k) ans = max(ans, dp[n-1][c]);
    rep(i, 0, n) ans += natural[i];
    cout << ans << "\n";
}

signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve();
    
    return 0;
}
