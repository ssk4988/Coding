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

const int MOD = 1e9+7;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    int n2 = 1 << n;
    vector dp(m+1, vector(n, vi(n2)));
    dp[0][0][0] = 1;
    rep(c, 0, m){
        rep(r, 0, n){
            rep(mask, 0, n2){
                if(dp[c][r][mask] == 0) continue;
                (dp[c + (r == n-1)][(r+1) % n][mask ^ (1 << r)] += dp[c][r][mask]) %= MOD;
                if(r + 2 <= n) {
                    if(((mask >> r) & 3) == 0){
                        (dp[c + (r == n-2)][(r+2) % n][mask] += dp[c][r][mask]) %= MOD;
                    }
                }
            }
        }
    }
    cout << dp[m][0][0] << "\n";
    
    return 0;
}
