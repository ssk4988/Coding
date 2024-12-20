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
	static constexpr T unit = INT_MIN;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
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
        Tree t(n);
        vvi adj(n);
        rep(i, 0, n-1){
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);adj[v].pb(u);
        }
        int q; cin >> q;
        vii qs(q);
        vvi buckets(n);
        rep(i, 0, q){
            cin >> qs[i].f >> qs[i].s;
            qs[i].f--;
            buckets[qs[i].f].pb(i);
        }
        vi ans(q);
        vi height(n);
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            for(int v : adj[u]) if (v != p) {
                dfs(v, u, dfs);
                height[u] = max(height[u], 1 + height[v]);
            }
        };
        dfs(0, -1, dfs);
        auto dfs1 = [&](int u, int p, int depth, auto &&dfs1) -> void {
            multiset<int> s;
            for(int v : adj[u]) if(v != p) {
                s.insert(height[v] + 1);
            }

            for(int v : adj[u]) if(v != p) {
                s.erase(s.find(height[v] + 1));
                int cur = sz(s) == 0 ? 0 : *s.rbegin();
                t.update(depth, cur - depth);
                dfs1(v, u, depth+1, dfs1);
                s.insert(height[v] + 1);
            }
            int cur = sz(s) == 0 ? 0 : *s.rbegin();
            t.update(depth, cur - depth);
            for(int qid : buckets[u]) {
                auto [u_1, k] = qs[qid];
                ans[qid] = max(0, depth + t.query(max(0, depth-k), depth+1));
            }
        };
        dfs1(0, -1, 0, dfs1);
        rep(i, 0, q){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }    
    
    return 0;
}
