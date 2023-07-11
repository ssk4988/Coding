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
ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    n++;
    vvi pref(n,vi(n)), suff(n, vi(n));
    rep(i, 0, m){
        int a, b; string str; cin >> a >> b >> str;
        int v = 1 << (str.compare("different") == 0); // 1 same 2 different 3 both
        pref[b][a] |= v; suff[b][a] |= v;
    }
    rep(i, 0, n){
        rep(j, 1, n){
            pref[i][j] |= pref[i][j - 1];
        }
        for(int j = n - 2; j >= 0; j--){
            suff[i][j] |= suff[i][j + 1];
        }
    }
    vvl dp(n, vl(n));
    dp[1][0] = (pref[1][1] & 2) == 0 ? 2 : 0;
    rep(i, 1, n - 1){
        rep(j, 0, i){
            // diff this one
            if((pref[i + 1][i] & 1) == 0 && (suff[i + 1][i + 1] & 2) == 0){
                dp[i + 1][i] = mod(dp[i + 1][i] + dp[i][j]);
            }
            if((pref[i + 1][j] & 1) == 0 && (suff[i + 1][j + 1] & 2) == 0){
                dp[i + 1][j] = mod(dp[i + 1][j] + dp[i][j]);
            }
        }
    }
    ll ans = 0;
    rep(i, 0, n){
        ans = mod(ans + dp[n - 1][i]);
    }
    cout << ans << "\n";


    
    return 0;
}