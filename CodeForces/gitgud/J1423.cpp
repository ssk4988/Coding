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
#define bitat(x, b) (((x) >> (b)) & 1)

int dp[62][8];
const int MOD = 1e9 + 7;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll x; cin >> x;
        x = x/2+2;
        x %= MOD;
        x *= x;
        x %= MOD;
        x *= 250000002;
        x %= MOD;
        cout << x << "\n";
        // memset(dp, -1, sizeof dp);
        // rep(bit, 0, 62) {
        //     rep(v, 0, 9) {
        //         auto& ans = dp[bit][v];
        //         int cnt = v*2;
        //         cnt += bitat(x, bit);
        //         if(bit == 0){ ans = cnt < 8; continue; }
        //         ans = 0;
        //         for(int nxt = 0; cnt >= 0 && nxt < 8; cnt--, nxt++) {
        //             if(cnt < 8) { 
        //                 ans += dp[bit-1][nxt];
        //                 if(ans >= MOD) ans -= MOD;
        //             }
        //         }
        //     }
        // }
        // cout << dp[61][0] << "\n";
    }
    
    return 0;
}
