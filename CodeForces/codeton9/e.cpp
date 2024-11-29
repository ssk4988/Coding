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

const ll MOD = 998244353;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        // CHECK: n=2, 3, 4, 5
        if(n == 2){
            cout << "1\n";
            continue;
        }
        // 0*01 - k = 0
        ll ans = 1;
        // 0*0101* - k = 1
        ans += n-3+1;
        vl dp(n+1); // state is length, number of length n arrays where k >= 2 and k not in array
        rep(len, 3, n){
            // len <= n-1
            // 0*010 1* then add something in prefix
            dp[len+1] = len-1;
        }
        // ll pref = 0;
        // allow arbitrary 1s after prefix
        rep(i, 1, n+1){
            (dp[i] += dp[i-1]) %= MOD;
        }
        // ans += (dp[n-1]) %= MOD;
        ll pref = 0;
        rep(i, 0, n+1){
            (dp[i] += pref) %= MOD;
            (pref += dp[i] * i) %= MOD;
        }
        // add as many k's as we want at end
        rep(i, 0, n+1)
        (ans += dp[i]) %= MOD;
        cout << ans << "\n";
    }
    
    return 0;
}
