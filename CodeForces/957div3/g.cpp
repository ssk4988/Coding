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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const ll mod = 1e9 + 7;
// inline ll mod(ll k){
//     return k % MOD;
// }

// const int mod = 17; /**< must be prime */
vector<int64_t> inv(2, 1), fact(inv), inv_fact(inv);
/**
 * @param n,k integers with n < mod
 * @returns number of ways to choose k objects out of n
 * @time O(1) amortized
 * @space O(1) amortized
 */
inline int64_t C(int n, int k) {
  assert(n < mod);
  if (k < 0 || n < k) return 0;
  while ((int)sz(inv) <= n) {
    int i = (int)sz(inv);
    inv.push_back(mod - (mod / i) * inv[mod % i] % mod);
    fact.push_back(i * fact[i - 1] % mod);
    inv_fact.push_back(inv[i] * inv_fact[i - 1] % mod);
  }
  return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        ll ans = 0;
        for(int i = 1; i <= 2 * n + 10; i++) {
            for(int j = 0; j <= min(n, i-1); j++) {
                int inside = i - (j+1);
                ll ways = (C(min(n, i-1), inside) * (j - inside == 0 ? 1 : C(n - i, j - inside))) % mod;
                // cout << i << " " << j << " " << ways << "\n";
                ans = (ans + ways * i) % mod;
            }
        }
        // vector<vl> dp(n+1, vl(2 * n + 10));
        // ll ans = 1;
        // dp[0][1] = 1;
        // rep(i, 0, n){
        //     rep(j, 0, sz(dp[i])){
        //         dp[i+1][j]
        //     }
        // }
        cout << ans << "\n";
    }
    
    return 0;
}
