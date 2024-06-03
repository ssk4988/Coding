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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
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
    int n; cin >> n;
    map<ll, int> rl;
    vll eq(n);
    rep(i, 0, n){
        cin >> eq[i].f >> eq[i].s;
        if(!rl.count(eq[i].f * eq[i].s)) rl[eq[i].f * eq[i].s] = sz(rl);
        if(!rl.count(eq[i].f + eq[i].s)) rl[eq[i].f + eq[i].s] = sz(rl);
        if(!rl.count(eq[i].f - eq[i].s)) rl[eq[i].f - eq[i].s] = sz(rl);
    }
    int source = 4 * n + sz(rl), sink = 4 * n + sz(rl) + 1;
    Dinic d(sink+1);
    rep(i, 0, n){
        d.addEdge(source, 4*i, 1);
        d.addEdge(4*i, 4*i+1, 1);
        d.addEdge(4*i, 4*i+2, 1);
        d.addEdge(4*i, 4*i+3, 1);
        auto [a, b] = eq[i];
        d.addEdge(4*i+1, 4*n+rl[a*b], 1);
        d.addEdge(4*i+2, 4*n+rl[a+b], 1);
        d.addEdge(4*i+3, 4*n+rl[a-b], 1);
    }
    for(auto [key, val] : rl) d.addEdge(4*n+val, sink, 1);
    ll mf = d.calc(source, sink);
    if(mf != n) {
        cout << "impossible\n";
        return 0;
    }
    rep(i, 0, n){
        int s = -1;
        for(auto e : d.adj[4*i]){
            if(e.flow() == 1 && e.to <= 4*i+3 && 4*i+1 <= e.to){
                s = e.to - (4*i+1);
            }
        }
        cout << eq[i].f << " ";
        if(s == 0) cout << "*";
        else if(s == 1) cout << "+";
        else cout << "-";
        cout << " " << eq[i].s << " = ";
        if(s == 0) cout << eq[i].f * eq[i].s << "\n";
        else if(s == 1) cout << eq[i].f+eq[i].s << "\n";
        else cout << eq[i].f-eq[i].s << "\n";
    }


    
    return 0;
}
