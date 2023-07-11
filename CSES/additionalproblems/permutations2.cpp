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

ll MOD = 1e9 + 7;
ll mod(ll k) {
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<vvl> dp(n + 1, vvl(n + 1, vl(3)));
    dp[0][0][0] = 1;

    rep(i, 0, n){
        rep(j, 0, i + 1){
            rep(k, 0, 3){
                if(dp[i][j][k] == 0) continue;
                if(j >= 2){
                    dp[i + 1][j - 1][0] = mod(dp[i + 1][j - 1][0] + mod(mod((j - 1) * (j - k)) * dp[i][j][k]));
                }
                if(j >= 1){
                    dp[i + 1][j][1] = mod(dp[i + 1][j][1] + mod(max(0, 2 * j - k) * dp[i][j][k]));
                }
                if(j + 1 <= i + 1){
                    dp[i + 1][j + 1][2] = mod(dp[i + 1][j + 1][2] + dp[i][j][k]);
                }
            }
        }
    }
    if(n == 1) cout << 1 << nL;
    else cout << mod(dp[n][1][0] + dp[n][1][1])<< nL;
    return 0;
}