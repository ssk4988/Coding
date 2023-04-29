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
    string str1, str2; cin >> str1 >> str2;
    int n = sz(str1), m = sz(str2);
    n++, m++;
    int BLANK = -1;
    vvi dp(n, vi(m, BLANK));
    dp[0][0] = 0;
    auto solve = [&](int i, int j, auto &&solve) -> int{
        if(dp[i][j] != BLANK) return dp[i][j];
        dp[i][j] = INT_MAX;
        if(i>0 && j>0){
            dp[i][j] = min(dp[i][j], (str1[i - 1] != str2[j - 1]) + solve(i - 1, j - 1, solve));
        }
        if(i > 0) dp[i][j] = min(dp[i][j], 1 + solve(i - 1, j, solve));
        if(j > 0) dp[i][j] = min(dp[i][j], 1 + solve(i, j - 1, solve));
        // cout << i << " " << j << " " << dp[i][j] <<  nL;
        return dp[i][j];
    };
    cout << solve(n - 1, m - 1, solve) << nL;
    
    return 0;
}