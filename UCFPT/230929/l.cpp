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

pair<ll, vl> hungarian(const vector<vl> &a) {
	if (a.empty()) return {0, {}};
	ll n = sz(a) + 1, m = sz(a[0]) + 1;
	vl u(n), v(m), p(m), ans(n - 1);
	rep(i,1,n) {
		p[0] = i;
		ll j0 = 0; // add "dummy" worker 0
		vl dist(m, LLONG_MAX), pre(m, -1);
		vector<bool> done(m + 1);
		do { // dijkstra
			done[j0] = true;
			ll i0 = p[j0], j1, delta = LLONG_MAX;
			rep(j,1,m) if (!done[j]) {
				auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
			rep(j,0,m) {
				if (done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		} while (p[j0]);
		while (j0) { // update alternating path
			ll j1 = pre[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
	rep(j,1,m) if (p[j]) ans[p[j] - 1] = j - 1;
	return {-v[0], ans}; // min cost
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vl> prod(n, vl(m));
    ll inf = 1e15;
    rep(i, 0, n){
        rep(j, 0, m){
            cin >> prod[i][j];
        }
    }
    vector<vl> adj(n, vl(n));
    rep(i, 0, n){
        rep(j, 0, n){
            ll v; cin >> adj[i][j];
            if(adj[i][j] == -1) adj[i][j] = inf;
        }
    }
    rep(i, 0, n) adj[i][i] = 0;
    rep(k, 0, n){
        rep(i, 0, n){
            rep(j, 0, n){
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
    vector<vl> cost(m, vl(n));
    rep(i, 0, m){
        rep(j, 0, n){
            rep(k, 0, n){
                cost[i][j] += adj[k][j] * prod[k][i];
            }
        }
    }
    auto [tot, matching] = hungarian(cost);
    cout << tot << nL;

    
    return 0;
}
