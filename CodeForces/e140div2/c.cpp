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

int MOD = 998244353;

int mod(int k){
    return (k % MOD + MOD) % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi vals(n + 1, vi(n + 1, 0));
    rep(i, 0, n){
        rep(j, 0, n - i){
            cin >> vals[i + 1][i + j + 1];
        }
    }
    vvi dp(n + 1, vi(n + 1, 0));
    dp[1][0] = vals[1][1] == 2 ? 0 : 2;
    int ans = 0;
    rep(i, 1, n){
        rep(j, 0, n + 1){
            if (j >= i) continue;
            // to validate i + 1 check i 
            // same
            bool same = true;
            bool diff = true;
            rep(k, 1, i + 2){
                if(vals[k][i + 1] == 1 && k <= i) diff = false;
                if(vals[k][i + 1] == 1 && k <= j) {
                    diff = same = false;
                }
                if(vals[k][i + 1] == 2 && k > j) same = false;
            }
            if(vals[i + 1][i + 1] == 2){
                diff = same = false;
            }
            if(same){
                dp[i + 1][j] = mod(dp[i + 1][j] + dp[i][j]);
            }
            if(diff){
                dp[i + 1][i] = mod(dp[i + 1][i] + dp[i][j]);
            }
        }
    }
    rep(i, 0, n + 1){
        ans = mod(ans + dp[n][i]);
    }
    cout << ans << nL;
    return 0;
}