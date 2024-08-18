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

const ll MOD = 998244353;
inline ll mod(ll k) {
    return (k % MOD + MOD) % MOD;
}
inline pl mod(pl k){
    return {mod(k.f), mod(k.s)};
}
pl operator+(pl a, pl b){
    return mod({a.f + b.f, a.s + b.s});
}
pl operator-(pl a, pl b){
    return mod({a.f - b.f, a.s - b.s});
}

pl operator*(pl a, ll k){
    return mod({a.f * k, a.s * k});
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vector<vpl> dp(n+1, vpl(k+1));
    vector<vpl> pref(n+1, vpl(k+1));
    pref[0][0] = {1, 0};
    pref[0][1] = {mod(-1), 0};
    rep(i, 0, n+1){
        rep(j, 0, k){
            if(j) {
                pref[i][j] = pref[i][j] + pref[i][j-1];
            }
            dp[i][j] = dp[i][j] + pref[i][j];
            if(i == n) continue;
            pref[i+1][1] = pref[i+1][1] + dp[i][j];
            pref[i+1][j+1] = pref[i+1][j+1] - dp[i][j];
            if(j == k-1){
                pref[i+1][0] = pref[i+1][0] + dp[i][j];
                pref[i+1][0].s = mod(pref[i+1][0].s + dp[i][j].f);
                pref[i+1][1] = pref[i+1][1] - dp[i][j];
                pref[i+1][1].s = mod(pref[i+1][1].s - dp[i][j].f);
            }
            else{
                pref[i+1][j+1] = pref[i+1][j+1] + dp[i][j] * (k - j);
                if(j+2 <= k){
                    pref[i+1][j+2] = pref[i+1][j+2] - dp[i][j] * (k - j);
                }
            }
        }
    }
    // rep(i, 0, n+1){
    //     rep(j, 0, k){
    //         cout << i << " " << j << " ways: " << dp[i][j].f << " score: " << dp[i][j].s << "\n";
    //     }
    // }
    ll ans = 0;
    rep(j, 0, k){
        ans = mod(ans + dp[n][j].s);
    }
    cout << ans << "\n";
    return 0;
}