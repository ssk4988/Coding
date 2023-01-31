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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int m, e;
        cin >> m >> e;
        vector<vvi> streets;
        map<string, int> conv;
        map<int, string> rconv;
        int nst = 0;
        string s1; getline(cin, s1);
        rep(i, 0, e){
            string str;
            getline(cin, str);
            vi a(3);
            rep(j, 0, 3){
                int ind = str.find(',');
                a[j] = stoi(str.substr(0, ind));
                str.erase(str.begin(), str.begin() + ind + 1);
            }
            if(conv.find(str) == conv.end()){
                conv[str] = nst++;
                rconv[conv[str]] = str;
                streets.pb({});
            }
            streets[conv[str]].pb(a);
        }
        vector<ll> flows;
        rep(v, -1, (int)(streets.size())){
            Dinic d(m);
            rep(i, 0, streets.size()){
                rep(j, 0, streets[i].size()){
                    d.addEdge(streets[i][j][0], streets[i][j][1], streets[i][j][2] + (v == i ? 1000000 : 0));
                }
            }
            flows.pb(d.calc(0, m - 1));
        }
        int best = 0;
        rep(i, 0, streets.size()){
            if(flows[i + 1] > flows[best + 1]){
                best = i;
            }
        }
        cout << rconv[best] << " " << (flows[best + 1] - flows[0]) << nL;
    }
    
    return 0;
}
