#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const ll MOD = 998244353;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc; 
    int LIM = 1e5+10;
    vvi divs(LIM);
    vi mobius(LIM);
    mobius[1] = 1;
    rep(i, 1, LIM){
        for(int j = i; j < LIM; j += i) divs[j].pb(i);
        for(int j = 2 * i; j < LIM; j += i) mobius[j] -= mobius[i];
    }
    rep(cn, 0, nc){
        int n; cin >> n;
        vl dp(n+1);
        vl sm(n+1), smmob(n+1);
        ll ans = 0;
        for(int x = n; x > 0; x--) {
            // for(int d1 : divs[x]){
            //     for(int d2 : divs[d1]){
            //         (sm[d2] -= dp[d1]) %= MOD;
            //     }
            // }
            vl dps;
            for(int j : divs[x]){
                dps.pb(dp[j]);
                (dp[j] -= 2 * dp[j]) %= MOD;
            }
            for(int j : divs[x] | views::reverse){
                smmob[j] = 2 * sm[j];
                for(int d : divs[x/j]){
                    if(d > 1) (smmob[j] -= smmob[j * d]) %= MOD;
                    // (dp[j] += 2 * sm[j * d] * mobius[d]) %= MOD;
                }
                (dp[j] += smmob[j]) %= MOD;
                // for(int d2 : divs[d1]){
                //     (dp[d2] += 2 * sm[d1] * mobius[d1 / d2]) %= MOD;
                // }
            }
            dp[x] += 1; // start here with first element
            rep(i, 0, sz(divs[x])){
                int d = divs[x][i];
                for(int d1 : divs[d]){
                    (sm[d1] -= dps[i]) %= MOD;
                }
                for(int d1 : divs[d]){
                    (sm[d1] += dp[d]) %= MOD;
                }
            }
        }
        rep(i, 1, n+1) (ans += dp[i]) %= MOD;
        (ans += MOD) %= MOD;
        cout << ans << "\n";
    }
    
    return 0;
}
