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

ll mod;

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n >> mod;
    ll ans = 0;
    grow(n+5);
    rep(i, n/2+1, n) {
        ll skipped = i-1;
        if(skipped == 0) continue;
        ll unskipped = n-2-skipped;
        ll under = 0;
        rep(j, 1, i){
            if(abs(j-0) <= n/2 && abs(j-i) <= n/2) under++;
        }
        rep(used, 0, unskipped+1) {
            ll cont = C(unskipped, used);
            // grow(skipped-1+(unskipped-used)+5);
            ll left = under * t[skipped-1+(unskipped-used)].fact % mod;
            (ans += cont * left) %= mod;
        }
    }
    // handle 0
    if(n % 2 == 0){
        (ans += t[n-2].fact) %= mod;
    }
    (ans *= n) %= mod;
    cout << ans << "\n";
    
    return 0;
}
