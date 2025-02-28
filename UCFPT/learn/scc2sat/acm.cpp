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

vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g,f));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi adj(n);
    vi tp(m);
    vector<vii> adj2(n);
    rep(i, 0, m) {
        int u, v, t; cin >> u >> v >> t; u--, v--;
        tp[i] = t;
        adj[u].pb(v);
        adj2[u].pb({v, i});
        if(t==2) adj[v].pb(u), adj2[v].pb({u, i});
    }
    bool inf = false;
    vvi comps;
    UF uf(n);
    scc(adj, [&](vi c)->void {
        comps.pb(c);
        set<int> did;
        for(int u : c) {
            for(auto [v, eid] : adj2[u]) {
                if(comp[v] != comp[u]) continue;
                if(tp[eid] == 1) {
                    inf = true;
                    return;
                }
                if(did.count(eid)) continue;
                did.insert(eid);
                if(!uf.join(u, v)) {
                    inf = true;
                    return;
                }
            }
        }
    });
    if(inf) {
        cout << "Infinite\n";
        return 0;
    }
    vi dp(n, -1), rdp(n, -1);
    rep(c, 0, ncomps) {
        auto dfs = [&](int u, int pid, auto &&dfs) -> void {
            dp[u] = 0;
            for(auto [v, eid] : adj2[u]) if(pid != eid) {
                if(comp[v] == comp[u]) {
                    dfs(v, eid, dfs);
                    dp[u] = max(dp[u], 1 + dp[v]);
                }
                else dp[u] = max(dp[u], 1 + rdp[v]);
            }
        };
        dfs(comps[c][0], -1, dfs);
        auto reroot = [&](int u, int pid, int pv, auto &&reroot) -> void {
            multiset<int> children;
            if(pid != -1) children.insert(1+pv);
            for(auto [v, eid] : adj2[u]) if(pid != eid) {
                children.insert(1+(comp[v] == comp[u] ? dp[v] : rdp[v]));
            }
            rdp[u] = sz(children) ? *rbegin(children) : 0;
            for(auto [v, eid] : adj2[u]) if(pid != eid) {
                if(comp[v] != comp[u]) continue;
                children.erase(children.find(dp[v]+1));
                reroot(v, eid, sz(children) ? *rbegin(children) : 0, reroot);
                children.insert(dp[v]+1);
            }
        };
        reroot(comps[c][0], -1, -1, reroot);
    }
    cout << *max_element(all(rdp)) << "\n";
    
    return 0;
}
