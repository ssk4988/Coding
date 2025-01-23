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
const ll inf = 1e18;
ll nc2(ll n) {
    return n * (n-1) / 2;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vll dp(n+1, {inf, inf});
    dp[0] = {0, 0};
    rep(i, 0, n) {
        rep(j, 1, n+5) {
            ll cnt = nc2(j);
            if(i + cnt > n) break;
            dp[i + cnt] = min(dp[i + cnt], {dp[i].f + j, dp[i].s + dp[i].f * j});
        }
    }    
    cout << dp[n].f << " " << dp[n].s << "\n";
    
    return 0;
}
