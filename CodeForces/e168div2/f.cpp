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

const int MOD = 998244353;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vi fib(3);
    fib[1] = fib[2] = 1;
    rep(i, 3, 100){
        fib.pb(fib[i - 1] + fib[i - 2]);
        if(fib[i] > 1000000000) break;
    }
    int n, x, m; cin >> n >> x >> m;
    const int MX = 60000;
    vi cnt(MX);
    cnt[1] = cnt[2] = 1;
    rep(i, 2, MX){
        auto it = prev(upper_bound(all(fib), i));
        cnt[i] = 1 + cnt[i - *it];
    }
    vvi dp(n+1, vi(MX));
    dp[0][0] = 1;
    rep(k, 1, x+1) {
        rep(i, 0, n){
            rep(j, 0, MX - fib[k] - 3){
                dp[i + 1][j + fib[k]] = dp[i + 1][j + fib[k]] + dp[i][j];
                if(dp[i + 1][j + fib[k]] >= MOD) dp[i + 1][j + fib[k]] -= MOD;
            }
        }
    }
    int ans = 0;
    rep(i, 0, MX){
        if(cnt[i] == m){
            ans = (ans + dp[n][i]) % MOD;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
