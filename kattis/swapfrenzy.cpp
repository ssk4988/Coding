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
    ll start; int k; cin >> start >> k;
    vi digs;
    while(start) {
        digs.pb(start % 10);
        start /= 10;
    }
    reverse(all(digs));
    bool dup = false;
    {
        vi seen(10);
        for(int d : digs) {
            if(seen[d]) dup = true;
            seen[d] = 1;
        }
    }
    vi ans;
    rep(len, 1, sz(digs)+1) {
        ans.pb(9);
        for(int dig = 9; dig >= 0; dig--) {
            ans.back() = dig;
            mcmf g(sz(digs)*2+2);
            int source = sz(digs)*2, sink = sz(digs)*2+1;
            rep(i, 0, sz(digs)) {
                g.add_edge(source, i, 1, 0);
                g.add_edge(sz(digs)+i, sink, 1, 0);
                rep(j, 0, sz(digs)) {
                    if(j < len && digs[i] != ans[j]) continue;
                    g.add_edge(i, sz(digs)+j, 1, i != j);
                }
            }
            auto [flow, cost] = g.calc(source, sink);
            bool works = flow == sz(digs);
            if(cost > k) works = false;
            if((cost&1) != (k&1) && !dup) works = false;
            cerr << len << " try " << dig << " " << works << " flow: " << flow << " cost: " << cost << " K: " << k << endl;
            if(works) break;
        }
    }
    for(int d : ans) cout << d;
    cout << "\n";
    
    
    return 0;
}
