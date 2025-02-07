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
	T f(T a, T b) { return a+b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
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
        int n; cin >> n;
        vi w(n);
        vvi bucket(n);
        rep(i, 0, n){
            cin >> w[i]; w[i]--;
            bucket[w[i]].pb(i);
        }
        vvi adj(n);
        rep(i, 0, n-1){
            int u, v; cin >> u >> v; u--, v--;
            adj[u].push_back(v);adj[v].pb(u);
        }
        int T = 0;
        vi tin(n), subsz(n, 1);
        auto dfs = [&](int u,int p, auto &&dfs) -> void {
            tin[u] = T++;
            for(int v : adj[u]) if(v != p) {
                dfs(v, u, dfs);
                subsz[u] += subsz[v];
            }
        };
        dfs(0, -1, dfs);
        Tree tree(n);
        vi bad(n);
        int prv = 0;
        for(int i = n-1; i >= 0; i--) {
            for(int u : bucket[i]) {
                if(tree.query(tin[u], tin[u] + subsz[u]) == prv){
                    bad[u] = true;
                }
            }
            for(int u : bucket[i]) {
                tree.update(tin[u], 1);
                prv += 1;
            }
        }
        Tree badtree(n), activetree(n);
        int ans = -1;
        for(int i = n-1; i >= 0; i--) {
            for(int u : bucket[i]) {
                int otheruse = activetree.query(0, tin[u]) + activetree.query(tin[u] + subsz[u], n);
                int baduse = badtree.query(0, tin[u]) + badtree.query(tin[u] + subsz[u], n);
                if(!bad[u] && baduse == otheruse){
                    ans = u;
                }
            }
            for(int u : bucket[i]) {
                badtree.update(tin[u], bad[u]);
                activetree.update(tin[u], 1);
            }
        }
        if(ans == -1) cout << 0 << "\n";
        else cout << ans+1 << "\n";
    }
    
    return 0;
}
