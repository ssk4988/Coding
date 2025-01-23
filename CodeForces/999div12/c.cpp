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

const int mod = 998244353;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi a(n);
        rep(i,0,n) cin >> a[i];
        vector<vl> dp(n, vl(2));
        dp[0][0] = 1;
        if(a[0] == 0) dp[0][1] = 1;
        rep(i, 0, n-1){
            int prv = i == 0 ? 0 : a[i-1];
            if(a[i+1] <= i+1 && a[i+1]-1 == prv){
                (dp[i+1][1] += dp[i][0]) %= mod;
            }
            if(a[i+1] == a[i]){
                (dp[i+1][1] += dp[i][1]) %= mod;
            }
            (dp[i+1][0] += dp[i][1]) %= mod;
        }
        int ans = dp[n-1][0] + dp[n-1][1];
        ans %= mod;
        cout << ans << "\n";
    }
    
    return 0;
}
