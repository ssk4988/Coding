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

const ll mod = 998244353;
struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  for (int i = sz(t); i < n + 1; i++) {
    int64_t inv = mod - (mod / i) * t[mod % i].inv % mod;
    t.push_back({inv, i * t[i - 1].fact % mod,
      inv * t[i - 1].inv_fact % mod});
  }
}
//! n,k < mod
//! @time O(1) amortized
//! @space O(1) amortized
int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return t[n].fact * t[k].inv_fact % mod *
    t[n - k].inv_fact % mod;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi a(n), freq(n);
        rep(i, 0, n) {
            cin >> a[i];
            freq[a[i]]++;
        }
        vector<vll> dp(n);
        // {ways, sum}
        {
            dp[0].resize(freq[0]+1);
            rep(i, 0, sz(dp[0])) {
                dp[0][i].f = C(freq[0], i);
                dp[0][i].s = C(freq[0], i) * i % mod;
            }
        }
        rep(i, 1, n) {
            dp[i].resize(freq[i]+1);
            pll suffprv{0, 0};
            ll csum = 0;
            // vl csuff(sz(dp[i]));
            // rep(j, 0, sz(csuff)) csuff[j] = C(freq[i], j);
            // for(int j = sz(csuff)-2; j >= 0; j--) (csuff[j] += csuff[j+1]) %= mod;
            for(int j = max(sz(dp[i]), sz(dp[i-1]))-1; j >= 0; j--) {
                if(j < sz(dp[i])) {
                    (csum += C(freq[i], j)) %= mod;
                }
                if(j < sz(dp[i]) && j < sz(dp[i-1])) {
                    dp[i][j].f = C(freq[i], j) * suffprv.f % mod;
                    dp[i][j].s = C(freq[i], j) * (suffprv.s + suffprv.f * j % mod) % mod;
                    (dp[i][j].f += csum * dp[i-1][j].f) %= mod;
                    (dp[i][j].s += csum * (dp[i-1][j].s + dp[i-1][j].f * j % mod)) %= mod;
                }
                if(j < sz(dp[i-1])) {
                    (suffprv.f += dp[i-1][j].f) %= mod;
                    (suffprv.s += dp[i-1][j].s) %= mod;
                }
            }
        }
        ll ans = 0;
        rep(i, 0, sz(dp.back())) (ans += dp.back()[i].s) %= mod;
        cout << ans << "\n";
    }
    
    return 0;
}
