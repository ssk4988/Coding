#include <bits/stdc++.h>
using namespace std;

using ll = __int128_t;
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

using state = array<ll, 4>;
state combine(state parent, state child) {
    auto [tot1, sq1, d1, n1] = parent;
    auto [tot2, sq2, d2, n2] = child;
    return {tot1 + tot2 + n1 * n2 + 2 * d1 * n2 + 2 * d2 * n1 + 2 * d1 * d2 + sq1 * n2 + sq2 * n1, sq1 + sq2 + 2 * d2 + n2, d1 + d2 + n2, n1 + n2};
}

state decombine(state parent, state child) {
    auto [tot3, sq3, d3, n3] = parent;
    auto [tot2, sq2, d2, n2] = child;
    ll n1 = n3 - n2;
    ll d1 = d3 - d2 - n2;
    ll sq1 = sq3 - sq2 - 2 * d2 - n2;
    ll tot1 = tot3 - tot2 - n1 * n2 - 2 * d1 * n2 - 2 * d2 * n1 - 2 * d1 * d2 - sq1 * n2 - sq2 * n1;
    return {tot1, sq1, d1, n1};
}

vector<state> solve(vvi adj) {
    int n = sz(adj);
    vector<state> dp(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        dp[u] = {0, 0, 0, 1};
        for(int v : adj[u]) if(v != p) {
            dfs(v, u, dfs);
            dp[u] = combine(dp[u], dp[v]);
        }
    };
    dfs(0, -1, dfs);
    vector<state> reroot(dp);
    auto dfs1 = [&](int u, int p, state parent_dp, auto &&dfs1) -> void {
        if(p != -1) reroot[u] = combine(reroot[u], parent_dp);
        for(int v : adj[u]) if(v != p) {
            dfs1(v, u, decombine(reroot[u], dp[v]), dfs1);
        }
    };
    dfs1(0, -1, {0, 0, 0, 0}, dfs1);
    return reroot;
}

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    long long n, m; cin >> n;
    vvi adj1(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj1[u].push_back(v);
        adj1[v].push_back(u);
    }
    cin >> m;
    vvi adj2(m);
    rep(i, 0, m-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj2[u].push_back(v);
        adj2[v].push_back(u);
    }
    auto dp1 = solve(adj1);
    auto dp2 = solve(adj2);
    // {
    //     ll ans = 1e18;
    //     rep(i, 0, n) {
    //         rep(j, 0, m) {
    //             auto [tot, sq, d, nv] = combine(dp1[i], dp2[j]);
    //             ans = min(ans, tot);
    //         }
    //     }
    //     cout << ans << "\n";
    // }
    ll ans = 1e25;
    LineContainer lc;
    rep(i, 0, m) {
        auto [tot2, sq2, d2, n2] = dp2[i];
        lc.add(-(2 * d2), -(tot2 + 2 * d2 * n + sq2 * n));
    }
    rep(i, 0, n) {
        auto [tot1, sq1, d1, n1] = dp1[i];
        ll val = -lc.query(d1);
        ll cur = n * m + val + tot1 + 2 * d1 * m + sq1 * m;
        ans = min(ans, cur);
    }
    // cout << ans << "\n";
    vi res;
    while(ans) {
        res.push_back(ans % 10);
        ans /= 10;
    }
    reverse(all(res));
    for(int x : res) cout << x;
    cout << "\n";

    return 0;
}
