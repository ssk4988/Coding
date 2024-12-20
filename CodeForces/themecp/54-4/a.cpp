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

const ll mod = 1e9+7; //!< must be prime
struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  while (sz(t) <= n) {
    int64_t i = sz(t),
            inv = mod - (mod / i) * t[mod % i].inv % mod;
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

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

ll nc2(ll n){
    return n * (n-1) / 2 % mod;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m, k; cin >> n >> m >> k;
        ll ans = 0;
        rep(i, 0, m) {
            int a, b, f; cin >> a >> b >> f;
            (ans += f * modpow(nc2(n), mod-2) % mod * k) %= mod;
        }
        rep(t, 1, k+1){
            ll p = modpow(nc2(n), mod-2);
            ll q = (1 - p) % mod;
            ll cont = m * C(k, t) % mod * nc2(t) % mod * modpow(p, t) % mod * modpow(q, k-t) % mod;
            (ans += cont) %= mod;
        }
        ans = (ans % mod + mod) % mod;
        cout << ans << "\n";
    }
    
    return 0;
}
