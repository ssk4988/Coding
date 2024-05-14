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

const ll MOD = 1e9+7;
const int MAX_N = 5005;
ll dp[MAX_N][MAX_N];
// elements, increases

vector<int64_t> inv(2, 1), fact(inv), inv_fact(inv);
inline int64_t C(int n, int k) {
  assert(n < MOD);
  if (k < 0 || n < k) return 0;
  while ((int)(inv).size() <= n) {
    int i = (int)(inv).size();
    inv.push_back(MOD - (MOD / i) * inv[MOD % i] % MOD);
    fact.push_back(i * fact[i - 1] % MOD);
    inv_fact.push_back(inv[i] * inv_fact[i - 1] % MOD);
  }
  return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    dp[0][0] = 1;
    rep(n, 1, MAX_N){
      rep(k, 1, n+1){
        dp[n][k] = (dp[n-1][k-1] + (n-1) * dp[n-1][k] % MOD) % MOD;
      }
    }
    int n, left, right;
    while(true){
        cin >> n >> left >> right;
        if(n == 0) break;
        ll ans = 0;
        rep(i, 0, n){
            ll res = C(n-1, i) * dp[i][left-1] % MOD * dp[n - 1 - i][right-1] % MOD;
            (ans += res) %= MOD;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
