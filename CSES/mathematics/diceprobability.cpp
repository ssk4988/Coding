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
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, a, b; cin >> n >> a >> b;
    vector<vector<ld>> dp(n + 1, vector<ld>(6 * n + 5));
    dp[0][0] = 1;
    rep(i, 0, n){
        rep(j, 0, sz(dp[i])){
            rep(k, 1, 7){
                if(j + k < sz(dp[i + 1])) dp[i + 1][j + k] += dp[i][j] / 6;
            }
        }
    }
    ld sum = 0;
    rep(i, a, b + 1){
        sum += dp[n][i];
    }
    cout << fixed << setprecision(6) << sum << nL;
        
    
    return 0;
}