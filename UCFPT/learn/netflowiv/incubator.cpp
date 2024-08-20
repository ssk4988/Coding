#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

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
    int n; cin >> n;
    vvi adj(n, vi(n));
    rep(i, 0, n){
        string s; cin >> s;
        rep(j, 0, n){
            adj[i][j] = s[j] == 'Y';
        }
    }
    vvi protect(n, vi(n));
    auto dfs = [&](int u, int source, auto &&dfs) -> void {
        if(protect[source][u]) return;
        protect[source][u] = true;
        rep(v, 0, n){
            if(adj[u][v]) dfs(v, source, dfs);
        }
    };
    rep(i, 0, n){
        rep(j, 0, n) if(adj[i][j]) dfs(j, i, dfs);
    }
    vi bad(n);
    rep(i, 0, n){
        rep(j, 0, n){
            if(protect[i][j] && protect[j][i]) bad[i] = bad[j] = true;
        }
    }
    int numbad = accumulate(all(bad), 0);
    if(numbad == n){
        cout << 0 << "\n";
        return 0;
    }
    int source = 2 * n, sink = 2 * n + 1;
	Dinic d(2 * n + 2);
	rep(i, 0, n){
		if(!bad[i]){
			d.addEdge(source, 2 * i, 1);
			d.addEdge(2 * i + 1, sink, 1);
		}
		rep(j, 0, n){
			if(!bad[i] && !bad[j] && protect[i][j]) d.addEdge(2 * i, 2 * j + 1, 1);
		}
	}
	ll mf = d.calc(source, sink);
	int paths = n - mf - numbad;
	cout << paths << "\n";



    return 0;
}
