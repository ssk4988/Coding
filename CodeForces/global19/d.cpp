#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

void solve() {
    int n; cin >> n;
    int K = 100100;
    vl a(n), b(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    vl suff(n+1);
    rep(i, 0, n){
        cin >> b[i];
    }
    for(int i =n-1; i >= 0; i--) suff[i] = b[i] + a[i] + suff[i+1];
    vector dp(n+1, vl(K, 1e18));
    dp[n][0] = 0;
    for(int i = n-1; i >= 0; i--) {
        for(int k = 0; k < K; k++) {
            if(dp[i+1][k] == 1e18) continue;
            ll c = 0;//(a[i] * a[i] + b[i] * b[i]) * ll(n - 1 - i);
            if(k + a[i] < K) dp[i][k + a[i]] = min(dp[i][k + a[i]], dp[i+1][k] + 2 * (a[i] * k + b[i] * (suff[i+1] - k)));
            if(k + b[i] < K) dp[i][k + b[i]] = min(dp[i][k + b[i]], dp[i+1][k] + 2 * (b[i] * k + a[i] * (suff[i+1] - k)));
        }
    }
    ll ans = 1e18;
    rep(i, 0, K) ans = min(ans, dp[0][i]);
    rep(i, 0 ,n){
        ans += (n-1) * a[i] * a[i] + (n-1) * b[i] * b[i];
    }
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) solve();
    
    return 0;
}
