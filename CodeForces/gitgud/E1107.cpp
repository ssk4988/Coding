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
    int n; cin >> n;
    string str; cin >> str;
    vl a(n+1);
    rep(i, 0, n){
        cin >> a[i+1];
    }
    vl best(n+1);
    rep(i, 1, n+1){
        rep(j, 0, i+1){
            best[i] =max(best[i], best[j] + a[i - j]);
        }
    }
    vector<vector<vl>> dp(n+1, vector<vl>(n+1, vl(n+1)));
    // pref done, stopping point, consec
    for(int l = n - 1; l >= 0; l--) {
        rep(r, l+1, n+1){
            rep(k, 1, n+1){
                dp[l][r][k] = max(dp[l][r][k], best[k] + dp[l+1][r][1]);
                rep(m, l+1, r){
                    if(str[l] == str[m]) dp[l][r][k] = max(dp[l][r][k], dp[m][r][k+1] + dp[l+1][m][1]);
                }
            }
            // dp[l][r][0] = *max_element(all(dp[l][r]));
        }
    }
    cout << dp[0][n][1] << "\n";
    
    return 0;
}