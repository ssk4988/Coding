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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};


struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C, int root) : time(sz(C)), rmq((dfs(C,root,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

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
    int n; cin >> n;
    vi a(2*n);
    vvi occ(n);
    rep(i, 0, 2*n) {
        cin >> a[i]; a[i]--;
        occ[a[i]].pb(i);
    }
    vvi adj(2*n);
    rep(i, 0, 2*n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi ans;
    rep(i, 0, 2*n) ans.pb(i);
    reverse(all(ans));
    for(int root : occ[a[2*n-1]]) {
        int T = 0;
        vi tin(2*n), subsz(2*n, 1);
        vi par(2*n, -1);
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            tin[u] = T++;
            par[u] = p;
            for(int v : adj[u]) if(v != p) {
                dfs(v, u, dfs);
                subsz[u] += subsz[v];
            }
        };
        dfs(root, -1, dfs);
        LCA lca(adj, root);
        Tree tree(2*n);
        rep(i, 0, n) {
            int u = occ[i][0], v = occ[i][1];
            int l = lca.lca(u, v);
            // cerr << "lca of " << u+1 << " and " << v+1 << " is " << l+1 << endl;
            tree.update(tin[l], 1);
        }
        vi cand;
        vi vis(2*n);
        for(int i = 2*n-1; i >= 0; i--) {
            int cheaper = occ[a[i]][0];
            int under = tree.query(tin[i], tin[i] + subsz[i]);
            if(under) {
                cand.pb(i);
            } else {
                auto dfs2 = [&](int u, int p, auto &&dfs2) -> void {
                    if(vis[u]) return;
                    vis[u] = true;
                    int other = occ[a[u]][0] == u ? 1 : 0;
                    other = occ[a[u]][other];
                    tree.update(tin[other], 1);
                    for(int v : adj[u]) if(v != p) {
                        dfs2(v, u, dfs2);
                    }
                };
                dfs2(i, par[i], dfs2);
            }
        }
        // cerr << "root: " << root+1 << endl;
        // for(int u : cand) cerr << u+1 << " ";
        // cerr << endl;
        ans = min(ans, cand);
    }
    cout << sz(ans) << "\n";
    for(int u : ans) cout << u+1 << " ";
    cout << "\n";

    
    return 0;
}
