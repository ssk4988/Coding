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

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m; cin >> n >> m;
        vl fuse(n);
        vector<vl> mat(m, vl(n));
        rep(i, 0, n) cin >> fuse[i];
        rep(i, 0, m) {
            rep(j, 0, n) cin >> mat[i][j];
        }
        auto test = [&](ll lim) -> bool {
            Dinic d(n + m + 3);
            int source = n + m, sink = n + m + 1, extra = n + m + 2;
            rep(i, 0, n) {
                if(fuse[i] <= lim) d.addEdge(i, extra, 1);
                d.addEdge(source, i, 1);
            }
            d.addEdge(extra, sink, n-m);
            rep(i, 0, m) {
                rep(j, 0, n) {
                    if(mat[i][j] <= lim) d.addEdge(j, n+i, 1);
                }
                d.addEdge(n+i, sink, 1);
            }
            ll flow = d.calc(source, sink);
            return flow == n;
        };
        ll ans = -1;
        for(ll dif = 1LL << 31; dif; dif /= 2) {
            if(!test(ans + dif)) ans += dif;
        }
        ans++;
        cout << ans << "\n";
    }
    
    return 0;
}
