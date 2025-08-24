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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, ll>>> adj(n);
    vi in2(n), out2(n);
    const int big = 1e9;
    const ll inf = 1e18;
    vector<vl> cost(n, vl(n, inf));
    rep(i, 0, n) cost[i][i] = 0;
    ll base = 0;
    rep(i, 0, m) {
        int u, v; ll w; cin >> u >> v >> w;
        u--, v--;
        base += w;
        adj[u].push_back({v, w});
        cost[u][v] = min(cost[u][v], w);
        in2[v]++;
        out2[u]++;
    }
    rep(k, 0, n) {
        rep(i, 0, n) {
            rep(j, 0, n) cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
        }
    }
    vi canbelast(n, 1);
    rep(i, 0, n) {
        if(cost[0][i] == inf) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        rep(j, 0, n) {
            if(cost[j][i] == inf) canbelast[i] = false;
            if(cost[i][j] == inf && cost[j][i] == inf) {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
    }
    ll ans = inf;
    int source = n, sink = n+1;
    rep(last, 0, n) {
        if(!canbelast[last]) continue;
        int sumin = 0, sumout = 0;
        mcmf g(n+2);
        vi in(in2), out(out2);
        in[0]++;
        out[last]++;
        rep(i, 0, n) {
            int amt = min(in[i], out[i]);
            in[i] -= amt;
            out[i] -= amt;
            sumin += in[i];
            sumout += out[i];
        }
        rep(i, 0, n) {
            rep(j, 0, n) {
                if(i == j || cost[i][j] == inf) continue;
                if(in[i] && out[j]) g.add_edge(i, j, big, cost[i][j]);
            }
        }
        rep(i, 0, n) {
            if(in[i]) g.add_edge(source, i, in[i], 0);
            if(out[i]) g.add_edge(i, sink, out[i], 0);
        }
        auto [fl, co] = g.calc(source, sink);
        if(fl == sumin) ans = min(ans, co + base);
    }
    if(ans == inf) cout << "IMPOSSIBLE\n";
    else cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }
    
    return 0;
}
