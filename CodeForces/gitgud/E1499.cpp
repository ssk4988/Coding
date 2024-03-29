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

const ll MOD = 998244353;
inline ll mod(ll k) {
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string a, b; cin >> a >> b;
    int n = sz(a), m = sz(b);
    vector<vvl> dp(n + 1, vvl(m + 1, vl(8, -1)));
    // bits: [last][used b][used a] 8
    auto go = [&](int i, int j, int pre, auto &&go) -> ll {
        if(pre == 8){
            return 1;
        }
        ll &ans = dp[i][j][pre];
        if(ans != -1) return ans;
        ans = 0;
        int last = (pre >> 2) & 1;
        int usedb = (pre >> 1) & 1;
        int useda = pre & 1;
        if(usedb && useda){
            ans = mod(ans + go(i, j, 8, go));
        }
        if(i == n && j == m){
            return ans;
        }
        if(i < n && ((!useda && !usedb) || (!last && a[i-1] != a[i]) || (last && b[j-1] != a[i]))){
            ans = mod(ans + go(i+1, j, (usedb << 1) | (1 << 0), go));
        }
        if(j < m && ((!useda && !usedb) || (!last && a[i-1] != b[j]) || (last && b[j-1] != b[j]))){
            ans = mod(ans + go(i, j+1, (1 << 2) | (1 << 1) | useda, go));
        }
        return ans;
    };
    ll ans = 0;
    rep(i, 0, n){
        rep(j, 0, m){
            ans = mod(ans + go(i, j, 0, go));
        }
    }
    cout << ans << "\n";
    // vector<vector<vector<vvl>>> dp(n + 1, vector<vector<vvl>>(m + 1, vector<vvl>(3, vvl(3, vl(2, -1)))));
    // // pref a, pref b, sub a, sub b, last used
    // auto go = [&](int i, int j, int k1, int k2, int last, auto &&go) -> void {
    //     ll &ans = dp[i][j][k1][k2][last];
    //     if(ans != -1) return ans;
    //     ans = 0;
    //     if(k1 == 0 || k1 == 2){
    //         ans = mod(ans + go(i + 1, j, k1, k2, last, go)); // skip a
    //     }
    //     else if(k2 == 0 || k2 == 2){
    //         ans = mod(ans + go(i, j+1, k1, k2, last, go)) // skip b
    //     }
    //     if(k1 == 0 && (k2 == 0 || )){
    //         ans = mod(ans + go(i + 1, j, 1, k2, 0, go));
    //     }
    // };
    
    return 0;
}
