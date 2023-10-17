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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    const ll MOD = 100007;
    int m; cin >> m;
    m--; // input includes the central node, going against every example the problem gives
    const int maxedges = 8001;
    vl dp(maxedges);
    dp[0] = 1;
    dp[1] = 1;
    rep(i, 2, sz(dp)){
        if(i % 2 == 0)
            dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
        else
            dp[i] = (2 * dp[i - 2] + dp[i - 3]) % MOD;
    }
    ll ans = 0;
    // leftside is how many outer nodes are on the left of the cycle, rightside is for right for cycle
    rep(leftside, 0, m + 1){
        rep(rightside, 0, m + 1){
            if (rightside + leftside + 2 <= m) // at least 2 outer nodes belong to the cycle
                ans = (ans + dp[leftside * 2] * dp[rightside * 2]) % MOD;
        }
    }
    cout << ans << nL;
    return 0;
}
