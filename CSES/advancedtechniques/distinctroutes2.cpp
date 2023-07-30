#include <bits/stdc++.h>
#include <bits/extc++.h>
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



const ll INF = numeric_limits<ll>::max() / 4;
// typedef vector<ll> vl;

struct MCMF {
	int N;
	vector<vi> ed, red;
	vector<vl> cap, flow, cost;
	vi seen;
	vector<pi> par;
	vl dist, rel;

	MCMF(int N) :
		N(N), ed(N), red(N), cap(N, vl(N)), flow(cap), cost(cap),
		seen(N), dist(N), rel(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		this->cap[from][to] = cap;
		this->cost[from][to] = cost;
		ed[from].push_back(to);
		red[to].push_back(from);
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({0, s});

		auto relax = [&](int i, ll cap, ll cost, int dir) {
			ll val = di - rel[i] + cost;
			if (cap && val < dist[i]) {
				dist[i] = val;
				par[i] = {s, dir};
				if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
				else q.modify(its[i], {-dist[i], i});
			}
		};

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + rel[s];
			for (int i : ed[s]) if (!seen[i])
				relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
			for (int i : red[s]) if (!seen[i])
				relax(i, flow[i][s], -cost[i][s], 0);
		}
		rep(i,0,N) rel[i] = min(rel[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
			totflow += fl;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				if (r) flow[p][x] += fl;
				else flow[x][p] -= fl;
		}
		rep(i,0,N) rep(j,0,N) totcost += cost[i][j] * flow[i][j];
		return {totflow, totcost};
	}

	// If some costs can be negative, call this before maxflow:
	void setrel(int s) { // (otherwise, leave this out)
		fill(all(rel), INF); rel[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,0,N) if (rel[i] != INF)
				for (int to : ed[i]) if (cap[i][to])
					if ((v = rel[i] + cost[i][to]) < rel[to])
						rel[to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    MCMF mcmf(n + 1);
	rep(i, 0, m){
		int a, b; cin >> a >> b;
		a--,b--;
		mcmf.addEdge(a, b, 1, 1);
	}
    mcmf.addEdge(n - 1, n, k, 0);
    pl ans = mcmf.maxflow(0, n);
    if(ans.f < k){
		cout << "-1\n";
		return 0;
	}
	cout << ans.s << nL;
	vector<unordered_set<int>> flow(n + 1);
	rep(i, 0, n + 1){
		rep(j, 0, n + 1){
			if(mcmf.flow[i][j]) flow[i].insert(j);
		}
	}
	rep(i, 0, k){
		vi path;
		path.pb(0);
		while(path.back() != n - 1){
			assert(flow[path.back()].size());
			auto it = flow[path.back()].begin();
			int v = *it;
			flow[path.back()].erase(it);
			path.pb(v);
		}
		// path.pop_back();
		cout << sz(path) << nL;
		for(int i : path) cout << (i + 1) << " ";
		cout << nL;
	}
    
    return 0;
}