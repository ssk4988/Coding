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
    int sq = sqrt(1'000'000'100);
    vector<bool> composite(sq + 1);
    composite[0] = composite[1] = true;
    vi primes;
    rep(i, 2, sz(composite)){
        if(!composite[i]){
            primes.pb(i);
            for(int j = i * i; j < sz(composite); j += i){
                composite[j] = true;
            }
        }
    }
    int n, m; cin >> n >> m;
    set<int> ps;
    vi a(n);
    vector<map<int, int>> fv(n);
    rep(i, 0, n){
        cin >> a[i];
        int a1 = a[i];
        for(int p : primes){
            if(a1 % p == 0){
                while(a1 % p == 0){
                    fv[i][p]++;
                    a1 /= p;
                }
                ps.insert(p);
            }
        }
        if(a1 > 1){
            fv[i][a1]++;
            ps.insert(a1);
        }
    }
    vpi good(m);
    rep(i, 0, m){
        cin >> good[i].f >> good[i].s;
        good[i].f--;good[i].s--;    
        if(good[i].f % 2 == 1){
            swap(good[i].f, good[i].s);
        }
    }
    ll ans = 0;
    for(int p : ps){
        Dinic d(n + 2);
        int source = n;
        int sink = n + 1;
        for(int i = 0; i < n; i+= 2){
            if(fv[i][p] > 0)
                d.addEdge(source, i, fv[i][p]);
        }
        for(int i = 1; i < n; i+= 2){
            if(fv[i][p] > 0)
                d.addEdge(i, sink, fv[i][p]);
        }
        rep(i, 0, m){
            int i1 = good[i].f, i2 = good[i].s;
            int po = min(fv[i1][p], fv[i2][p]);
            if(po > 0)
                d.addEdge(i1, i2, po);
        }
        ll mf = d.calc(source, sink);
        ans += mf;
    }
    cout << ans << nL;

    
    return 0;
}
