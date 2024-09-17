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

const ll MOD = 1e9 + 7;
const ll inv2 = (MOD+1)/2;

struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  while ((int)sz(t) <= n) {
    int64_t i = (int)sz(t), inv = MOD - (MOD / i) * t[MOD % i].inv % MOD;
    t.push_back({inv, i * t[i - 1].fact % MOD, inv * t[i - 1].inv_fact % MOD});
  }
}
//! @param n,k integers with n < MOD
//! @returns number of ways to choose k objects out of n
//! @time O(1) amortized
//! @space O(1) amortized
int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return t[n].fact * t[k].inv_fact % MOD * t[n - k].inv_fact % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m, k; cin >> n >> m >> k;
        // vector<vl> dp(n+1, vl(n+1));
        // rep(i, 1, n+1) {
        //     dp[i][0] = 0;
        //     (dp[i][i] = dp[i-1][i-1] + k) %= MOD;
        //     rep(j, 1, i){
        //         (dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) * inv2) %= MOD;
        //     }
        // }
        vl p2(1, 1);
        rep(i, 0, n){
            p2.push_back((p2.back() * inv2) % MOD);
        }
        ll ans = 0;
        if(m == 0){
            ans = 0;
        } else if(m == n) ans = (n * ll(k)) % MOD;
        else {
            rep(i, 1, n) {
                ans += (k * p2[n - (i)]) % MOD * ((i * C(n - (i+1), n - m - 1)) % MOD) % MOD;
                ans %= MOD;
            }
        }
        // cout << dp[n][m] << "\n";
        cout << ans << "\n";
    }
    
    
    return 0;
}
