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

// #pragma GCC optimize ("trapv")
const ll MOD = 998244353;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vi cases;
    int nc; cin >> nc;
    int LIM = 1;
    rep(cn, 0, nc){
        int n; cin >> n;
        cases.pb(n);
        LIM = max(LIM, n + 10);
    }
    // int LIM = 1e6+10;
    // int LIM = 100;
    vvi divs(LIM);
    vi mobius(LIM);
    mobius[1] = 1;
    rep(i, 1, LIM){
        for(int j = i; j < LIM; j += i) divs[j].pb(i);
        for(int j = 2 * i; j < LIM; j += i) mobius[j] -= mobius[i];
    }
    ll ops = 0;
    vl ans(LIM);
    vl dp(LIM);
    vector<vl> sm(LIM);
    vl dpt(LIM);
    vl inv(LIM);
    rep(x, 1, LIM){
        for(int i : divs[x]) {
            dp[i] = -dpt[i];
            for(int j : divs[i]) {
                // if(j == i) continue;
                (dp[i] += inv[j]) %= MOD;
                // for(int d3 : divs[i/j]) {
                    // ops++;
                    // (dp[i] += 2 * sm[j][d3]) %= MOD;
                    // dp[i] = mod(dp[i] + mobius[d3] * mod(2 * sm[j][d3]));
                // }
            }
            (dp[i] *= 2) %= MOD;
            dp[i] += 1;
            dp[i] %= MOD;
        }
        ans[x] = (dp[x] + MOD) % MOD;
        for(int a : divs[x]) {
            (dpt[a] += dp[a]) %= MOD;
            for(int c : divs[a]) {
                (inv[a] += dp[c] * mobius[a/c]) %= MOD;
                // (sm[a][c] += dp[a] * mobius[c]) %= MOD;
            }
        }
    }
    rep(x, 1, LIM){
        ans[x] += ans[x-1];
        ans[x] %= MOD;
    }
    // rep(x, 1, 11) cout << ans[x] << endl;
    // cout << ops << endl;
    // int nc; cin >> nc; 
    rep(cn, 0, nc){
        // int n; cin >> n;
        cout << ans[cases[cn]] << "\n";
    }
    
    return 0;
}
