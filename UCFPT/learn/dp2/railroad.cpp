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


int c[2001], a[1001], b[1001];
bool solve(vector<vector<bool>>& dp, vector<vector<bool>>& ready, int i, int j){
    if(ready[i][j]) return dp[i][j];
    dp[i][j] = false;
    if(i > 0){
        dp[i][j] = dp[i][j] || solve(dp, ready, i - 1, j) && c[i + j - 1] == a[i - 1];
    }
    if(j > 0){
        dp[i][j] = dp[i][j] || solve(dp, ready, i, j - 1) && c[i + j - 1] == b[j - 1];
    }
    ready[i][j] = true;
    return dp[i][j];
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n = -1, m = -1;
    while(true){
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        rep(i, 0, n){
            cin >> a[i];
        }
        rep(i, 0, m){
            cin >> b[i];
        }
        //memset(c, 0, sizeof c);
        rep(i, 0, n + m){
            cin >> c[i];
        }
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        vector<vector<bool>> ready(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = ready[0][0] = true;
        cout << (solve(dp, ready, n, m) ? "possible" : "not possible") << nL;
    }
    
    return 0;
}