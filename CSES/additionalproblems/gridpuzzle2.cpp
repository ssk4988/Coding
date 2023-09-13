#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pii>;
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
typedef vector<ll> VL;

struct MCMF {
	int N;
	vector<vi> ed, red;
	vector<VL> cap, flow, cost;
	vi seen;
	VL dist, pi;
	vector<pii> par;

	MCMF(int N) :
		N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap),
		seen(N), dist(N), pi(N), par(N) {}

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
			ll val = di - pi[i] + cost;
			if (cap && val < dist[i]) {
				dist[i] = val;
				par[i] = {s, dir};
				if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
				else q.modify(its[i], {-dist[i], i});
			}
		};

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (int i : ed[s]) if (!seen[i])
				relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
			for (int i : red[s]) if (!seen[i])
				relax(i, flow[i][s], -cost[i][s], 0);
		}
		rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
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
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,0,N) if (pi[i] != INF)
				for (int to : ed[i]) if (cap[i][to])
					if ((v = pi[i] + cost[i][to]) < pi[to])
						pi[to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    MCMF d(2 * n + 2);
    vi a(n), b(n);
    rep(i, 0, n){
        int v; cin >> v;
        a[i] = v;
        d.addEdge(2 * n, i, v, 0);
    }
    rep(i, 0, n){
        int v; cin >> v;
        b[i] = v;
        d.addEdge(i + n, 2 * n + 1, v, 0);
        
    }
    rep(i, 0, n){
        rep(j, 0, n){
            int c; cin >> c;
            d.addEdge(i, j + n, 1, -c);
        }
    }
    d.setpi(2 * n);
    pl mf = d.maxflow(2 * n, 2 * n + 1);
    bool works = true;
    vvi grid(n, vi(n));
    rep(i, 0, n){
        rep(j, 0, n){
            if(d.flow[i][j + n]){
                grid[i][j] = 1;
                a[i]--;
                b[j]--;
                // cout << i << " " << j << " " << d.flow[i][j + n] << nL;
            }
        }
        // for(auto &e : d.adj[i]){
        //     if(e.flow()){
        //         grid[i][e.to - n] = 1;
        //         a[i]--;
        //         b[e.to - n]--;
        //         // cout << i << " " << (e.to - n) << " " << e.flow() << "\n";
        //     } 
        // }
    }
    rep(i, 0, n){
        if(a[i] || b[i]) works = false;
    }
    if(!works) cout << "-1\n";
    else{
        cout << abs(mf.second) << nL;
        rep(i, 0, n){
            rep(j, 0, n){
                cout << (grid[i][j] ? 'X' : '.');
            }
            cout << "\n";
        }
    }

    
    return 0;
}