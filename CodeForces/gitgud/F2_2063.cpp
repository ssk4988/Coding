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

const ll mod = 998244353; //!< must be prime
struct comb {
  int64_t inv = 1, fact = 1, inv_fact = 1;
};
vector<comb> t(2);
void grow(int n) {
  for (int i = ssize(t); i < n + 1; i++) {
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

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vl catalan(2*3e5+5);
    catalan[0]=1;
    rep(i, 1, sz(catalan)){
        catalan[i] = (C(2*i, i)-C(2*i, i+1)+mod)%mod;
    }
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        int m = 1;
        vvi child(1);
        vi par{-1};
        vi subsz{2*n+2};
        vi childsz{0};
        vi ls{-1}, rs{2*n};
        FT ft(2*n);
        set<pii> brackets;
        brackets.insert({-1, 0});
        brackets.insert({2*n, 0});
        auto calc = [&](int i) -> ll {
            int b = subsz[i]-2-childsz[i];
            b /= 2;
            return catalan[b];
        };
        ll ans = calc(0);
        cout << ans << " ";
        rep(qid, 0, n) {
            int l, r; cin >> l >> r; l--, r--;
            auto it = prev(brackets.lower_bound({l, -1}));
            int p = it->s;
            if(ls[p] != it->f) p = par[p];
            (ans *= modpow(calc(p), mod-2)) %= mod;
            int id = m++;
            child.pb({});
            child[p].pb(id);
            par.pb(p);
            subsz.pb(r-l+1);
            childsz.pb(ft.query(r+1)-ft.query(l));
            childsz[p] += subsz[id]-childsz.back();
            ls.pb(l), rs.pb(r);
            brackets.insert({l, id}), brackets.insert({r, id});
            (ans *= calc(id)) %= mod;
            (ans *= calc(p)) %= mod;
            cout << ans << " ";
        }
        cout << "\n";
    }


    
    return 0;
}
