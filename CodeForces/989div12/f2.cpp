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

const ll MOD = 998244353; //!< must be prime
struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  while (sz(t) <= n) {
    int64_t i = sz(t),
            inv = MOD - (MOD / i) * t[MOD % i].inv % MOD;
    t.push_back({inv, i * t[i - 1].fact % MOD,
      inv * t[i - 1].inv_fact % MOD});
  }
}
//! n,k < MOD
//! @time O(1) amortized
//! @space O(1) amortized
int64_t C(int n, int k) {
  if (k < 0 || n < k) return 0;
  grow(n);
  return t[n].fact * t[k].inv_fact % MOD *
    t[n - k].inv_fact % MOD;
}

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % MOD, e /= 2)
		if (e & 1) ans = ans * b % MOD;
	return ans;
}

ll modinv(ll b){
    return modpow(b, MOD-2);
}

void solve(int cn) {
    int n, m, k; cin >> n >> m >> k;
    vii conds(k);
    rep(i, 0, k){
        cin >> conds[i].f >> conds[i].s;
    }
    conds.pb({0, 0});
    conds.pb({n, m});
    sort(all(conds));
    k += 2;
    vl path2(k);
    path2[0] = 1;
    auto ways = [&](int i, int j) -> ll {
        auto [a, b] = conds[i];
        auto [c, d] = conds[j];
        return C(a-c + b-d, a-c);
    };
    rep(nxt, 0, k){
        rep(prv, 0, nxt){
            (path2[nxt] += path2[prv] * ways(nxt, prv)) %= MOD;
        }
    }
    ll ans = 0;
    rep(i, 0, k-1){
        ll later = ways(k-1, i);
        ll add = 2 * (n - conds[i].f) + (m - conds[i].s);
        (ans += add * later % MOD * path2[i]) %= MOD;
    }
    (ans *= modinv(C(n+m, m))) %= MOD;
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve(cn);
    }
    
    return 0;
}
