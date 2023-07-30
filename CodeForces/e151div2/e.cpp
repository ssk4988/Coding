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

const int offset = 60;
const ll MOD = 1e9 + 7;
ll mod(ll k){
    return k % MOD;
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vvl prevdp(2 * offset + 2, vl(k + 1)), dp(2 * offset + 2, vl(k + 1));
    prevdp[offset][0] = 1;
    rep(i, 0, n){
        rep(j, 0, sz(prevdp)){
            rep(l, 0, sz(prevdp[j])){
                if(prevdp[j][l] == 0) continue;
                int j1 = j - a[i], l1 = l + abs(j1 - offset);
                if(j1 >= 0 && j1 <= sz(dp) && l1 <= k){
                    dp[j1][l1] = mod(dp[j1][l1] + prevdp[j][l]);
                }
                j1 = j - a[i] + 1, l1 = l + abs(j1 - offset);
                if(j1 >= 0 && j1 <= sz(dp) && l1 <= k){
                    dp[j1][l1] = mod(dp[j1][l1] + prevdp[j][l]);
                }
            }
        }
        rep(j, 0, sz(prevdp)){
            rep(l, 0, sz(prevdp[j])){
                prevdp[j][l] = dp[j][l];
                dp[j][l] = 0;
            }
        }
    }
    ll ans = 0;
    rep(l, 0, k + 1){
        if((k - l) % 2 == 0){
            ans = mod(ans + prevdp[offset][l]);
        }
    }
    cout << ans << nL;
    
    return 0;
}
