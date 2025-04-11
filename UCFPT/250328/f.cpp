#include <bits/stdc++.h>
#pragma GCC target("avx2,popcnt")
#pragma GCC optimize("Ofast")
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

random_device rdev;
mt19937 rng(rdev());

template <bool VALS_EDGES> struct HLD {
	int N, tim = 0;
	vector<vi> adj;
	vi par, siz, rt, pos;
	HLD(vector<vi> adj_)
		: N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1),
		  rt(N),pos(N) { dfsSz(0); dfsHld(0); }
	void dfsSz(int v) {
		for (int& u : adj[v]) {
			adj[u].erase(find(all(adj[u]), v));
			par[u] = v;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(int u, int v, B op) {
		for (;; v = par[rt[v]]) {
			if (pos[u] > pos[v]) swap(u, v);
			if (rt[u] == rt[v]) break;
			op(pos[rt[v]], pos[v] + 1);
		}
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	vii queryPath(int u, int v) { 
		vii rs;
		process(u, v, [&](int l, int r) {
				rs.push_back({l, r});
		});
		return rs;
	}
};
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    HLD<0> hld(adj);
    vi a(n);
    rep(i, 0, n) {
        a[hld.pos[i]] = i+1;
    }
    rep(qid, 0, q) {
        string t; cin >> t;
        if(t == "?") {
            int u, v; cin >> u >> v; u--, v--;
            vii rs = hld.queryPath(u, v);
            int ans = 0;
            for(auto [l, r] : rs) {
                rep(i, l, r) ans ^= a[i];
            }
            cout << ans << "\n";
        }
        else {
            int u, v, x; cin >> u >> v >> x; u--, v--;
            vii rs = hld.queryPath(u, v);
            for(auto [l, r] : rs) {
                rep(i, l, r) a[i] += x;
            }
        }
    }

    return 0;
}
