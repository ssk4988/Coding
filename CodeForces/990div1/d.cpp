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

struct mcmf {
	const ll inf = LLONG_MAX >> 2;
	struct edge {
		int v;
		ll cap, flow, cost;
	};
	int n;
	vector<edge> edges;
	vvi adj; vii par; vi in_q;
	vector<ll> dist, pi;
	mcmf(int n): n(n), adj(n), dist(n), pi(n), par(n), in_q(n) {}
	void add_edge(int u, int v, ll cap, ll cost) {
		int idx = sz(edges);
		edges.push_back({v, cap, 0, cost});
		edges.push_back({u, cap, cap, -cost});
		adj[u].push_back(idx);
		adj[v].push_back(idx ^ 1);
	}
	bool find_path(int s, int t) {
		fill(all(dist), inf);
		fill(all(in_q), 0);
		queue<int> q; q.push(s); 
		dist[s] = 0, in_q[s] = 1;
		while(!q.empty()) {
			int cur = q.front(); q.pop();
			in_q[cur] = 0;
			for(int idx: adj[cur]) {
				auto [nxt, cap, fl, wt] = edges[idx];
				ll nxtD = dist[cur] + wt;
				if(fl >= cap || nxtD >= dist[nxt]) continue;
				dist[nxt] = nxtD;
				par[nxt] = {cur, idx};
				if(in_q[nxt]) continue;
				q.push(nxt); in_q[nxt] = 1;
			}
		}
 
		return dist[t] < inf;
	}
	pair<ll, ll> calc(int s, int t) {
		ll flow = 0, cost = 0;
		while(find_path(s, t)) {
			rep(i, 0, n) pi[i] = min(pi[i] + dist[i], inf);
			ll f = inf;
			for(int i, u, v = t; tie(u, i) = par[v], v != s; v = u)
				f = min(f, edges[i].cap - edges[i].flow);
			flow += f;
			for(int i, u, v = t; tie(u, i) = par[v], v != s; v = u)
				edges[i].flow += f, edges[i^1].flow -= f;
		}
		rep(i, 0, sz(edges)>>1)
			cost += edges[i<<1].cost * edges[i<<1].flow;
 
		return {flow, cost};
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m; cin >> n >> m;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        vvi adj(n);
        rep(i, 0, m){
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
        }
        {
            vvi reach(n, vi(n));
            auto dfs = [&](int u, int o, auto &&dfs)->void {
                if(reach[o][u]) return;
                reach[o][u] = true;
                for(int v : adj[u]) dfs(v, o, dfs);
            };
            rep(i, 0, n) dfs(i, i, dfs);
            vi belong(n, -1);
            int m = 0;
            rep(i, 0, n){
                if(belong[i] != -1) continue;
                rep(j, 0, n) if(reach[i][j] && reach[j][i]) belong[j] = m;
                m++;
            }
            vvi adj2(m);
            vi b(m);
            rep(i, 0, n){
                b[belong[i]] += a[i];
                for(int j : adj[i]){
                    if(belong[j] != belong[i]) adj2[belong[i]].pb(belong[j]);
                }
            }
            adj = adj2;
            a = b;
            n = m;
        }
        mcmf flow(3 * n + 4);
        int source = 3 * n, sink = 3 * n + 1;
        int ss = sink + 1, st = sink + 2;
        flow.add_edge(sink, source, 1000, 0);
        rep(i, 0, n){
            flow.add_edge(ss, 3 * i + 2, 1, 0);
            flow.add_edge(3 * i + 1, st, 1, 0);
            flow.add_edge(source, 3 * i, a[i], 0);
            flow.add_edge(3 * i, 3 * i + 1, a[i], 1);
            flow.add_edge(3 * i, 3 * i + 2, a[i], 0);
            flow.add_edge(3 * i + 1, 3 * i + 2, 1000, 0);
            // flow.add_edge(3 * i + 1, 3 * i + 2, 1, -1000);
            // flow.add_edge(3 * i + 2, 3 * i + 3, 1000, 0);
            for(int j : adj[i]) {
                flow.add_edge(3 * i + 2, 3 * j + 1, 1000, 0);
                // cout << i << "," << j << " " << cn << endl;
            }
            flow.add_edge(3 * i + 2, sink, 1, 0);
        }
        auto [mf, cost] = flow.calc(ss, st);
        // assert(mf == n);
        cerr << n << " " << cost << "\n";
        if(mf != n) {
            cout << "-1\n";
            continue;
        }
        cout << cost << "\n";
    }
    
    return 0;
}
