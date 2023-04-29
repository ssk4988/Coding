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
using vvl = vector<vl>;

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
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    ll sum = 0;
    rep(i, 0, n){
        cin >> a[i];
        sum += a[i];
    }
    int BLANK = -1;
    vvl dp(n, vl(n, BLANK));
    auto solve = [&](int i, int j, auto &&solve)->ll{
        // cout << i << " " << j << nL;
        if(i > j) return 0;
        if(dp[i][j] != BLANK) return dp[i][j];
        dp[i][j] = INT_MIN;
        dp[i][j] = max(a[i] - solve(i + 1, j, solve), a[j] - solve(i, j - 1, solve));
        return dp[i][j];
    };
    ll val = solve(0, n - 1, solve);
    ll av = (sum + val) / 2;
    cout << av << nL;
    return 0;
}