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

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int cur, int par) {
		time[cur] = T++;
		for (int nxt : C[cur]) if (nxt != par) {
			path.push_back(cur), ret.push_back(time[cur]);
			dfs(C, nxt, cur);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        vl w(n);
        rep(i, 0, n) cin >> w[i];
        vi c(n);
        bool filled = false;
        rep(i, 0, n) {
            cin >> c[i]; c[i]--;
            if(c[i] != -1) filled = true;
        }
        vvi adj(n);
        rep(i, 0, n-1) {
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        if(!filled) {
            cout << "0\n";
            rep(i, 0, n) cout << 1 << " ";
            cout << "\n";
            continue;
        }
        vvi subsets(k);
        rep(i, 0, n) if(c[i] != -1) subsets[c[i]].pb(i);
        LCA lca(adj);
        rep(i, 0, k) {
            sort(all(subsets[i]), [&](int u, int v) { return lca.time[u] < lca.time[v]; });
            rep(j, 1, sz(subsets[i])) {
                int u = subsets[i][j-1], v = subsets[i][j];
                int l = lca.lca(u, v);
                if(c[l] == -1) c[l] = i;
            }
        }
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            int decide = -1;
            for(int v : adj[u]) if(v != p) {
                dfs(v, u, dfs);
                if(c[v] != -1) decide = c[v];
            }
            if(decide != -1 && c[u] == -1) c[u] = decide;
        };
        dfs(0, -1, dfs);
        auto dfs2 = [&](int u, int p, int pcolor, auto &&dfs2) -> void {
            if(c[u] == -1) {
                assert(pcolor != -1);
                c[u] = pcolor;
            }
            for(int v : adj[u]) if(v != p) {
                dfs2(v, u, c[u], dfs2);
            }
        };
        dfs2(0, -1, -1, dfs2);
        subsets = vvi(k);
        ll ans = 0;
        vi cute(n);
        rep(i, 0, n) {
            subsets[c[i]].pb(i);
        }
        rep(i, 0, k) {
            sort(all(subsets[i]), [&](int u, int v) { return lca.time[u] < lca.time[v]; });
            rep(j, 1, sz(subsets[i])) {
                int u = subsets[i][j-1], v = subsets[i][j];
                int l = lca.lca(u, v);
                if(c[l] != i) cute[l] = 1;
            }
        }
        rep(i, 0, n) if(cute[i]) ans += w[i];
        cout << ans << "\n";
        rep(i, 0, n) {
            cout << c[i]+1 << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
