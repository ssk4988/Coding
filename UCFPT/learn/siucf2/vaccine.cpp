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

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] += val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, q; cin >> n >> q; 
        vvi adj(n);
        rep(i, 0, n-1) {
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vi tin(n);
        vi subsz(n, 1);
        int T = 0;
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            tin[u] = T++;
            for(int v : adj[u]) if(v != p) {
                dfs(v, u, dfs);
                subsz[u] += subsz[v];
            }
        };
        dfs(0, -1, dfs);
        Tree tree(n);
        rep(i, 0, q) {
            int u, v, t; cin >> u >> v >> t; u--, v--;
            if(t == 0) {
                int lower = tin[u] < tin[v] ? v : u;
                int ans = abs(tree.query(tin[lower], tin[lower] + subsz[lower]));
                cout << ans << "\n";
            } else {
                tree.update(tin[u], t), tree.update(tin[v], -t);
            }
        }
    }
    
    return 0;
}
