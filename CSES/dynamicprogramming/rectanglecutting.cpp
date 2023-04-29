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
    int a, b; cin >> a >> b;
    int BLANK = -1;
    vvi dp(a + 1, vi(b + 1, BLANK));
    rep(i, 0, min(a, b) + 1){
        dp[i][i] = 0;
    }
    auto solve = [&](int i, int j, auto &&solve) ->int{
        if(dp[i][j] != BLANK) return dp[i][j];
        dp[i][j] = INT_MAX;
        rep(k, 1, i){
            dp[i][j] = min(dp[i][j], 1 +solve(k, j, solve) + solve(i - k, j, solve));
        }
        rep(k, 1, j){
            dp[i][j] = min(dp[i][j],  1 +solve(i, k, solve) + solve(i, j - k, solve));
        }
        // cout << dp[i][j];
        return dp[i][j];
    };
    cout << solve(a, b, solve) << nL;
    
    return 0;
}