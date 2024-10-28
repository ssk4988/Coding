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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0, n-1) {
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vi par(n, -1), dep(n), subsz(n, 1), tin(n);
        int T = 0;
        auto dfs = [&](int u, auto &&dfs) -> void {
            tin[u] = T++;
            for(int v : adj[u]) if(v != par[u]) {
                dep[v] = 1 + dep[u];
                par[v] = u;
                dfs(v, dfs);
                subsz[u] += subsz[v];
            }
        };
        dfs(0, dfs);
        FT ft(n);
        set<int> use;
        vvi buckets(n+1);
        rep(i, 0, n) buckets[dep[i]].pb(i);
        int ans = 0;
        rep(d, 0, sz(buckets)) {
            for(int u : buckets[d]) {
                use.insert(u);
                ft.update(tin[u], 1);
            }
            if(d) {
                for(int u : buckets[d-1]) {
                    int c = u;
                    while(c != -1 && use.count(c) && ft.query(tin[c] + subsz[c]) - ft.query(tin[c]) <= 1) {
                        use.erase(c);
                        ft.update(tin[c], -1);
                        c = par[c];
                    }
                }
            }
            // cout << "depth " << d << " cnt: " << sz(use) << "\n";
            ans = max(ans, sz(use));
        }
        cout << n-ans << "\n";
    }
    
    return 0;
}
