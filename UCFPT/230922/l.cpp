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

pair<int, vi> hungarian(const vector<vi> &a) {
	if (a.empty()) return {0, {}};
	int n = sz(a) + 1, m = sz(a[0]) + 1;
	vi u(n), v(m), p(m), ans(n - 1);
	rep(i,1,n) {
		p[0] = i;
		int j0 = 0; // add "dummy" worker 0
		vi dist(m, INT_MAX), pre(m, -1);
		vector<bool> done(m + 1);
		do { // dijkstra
			done[j0] = true;
			int i0 = p[j0], j1, delta = INT_MAX;
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
			int j1 = pre[j0];
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
    int n; cin >> n;
    vvi worker(n, vi(2 * n));
    rep(i, 0, n){
        rep(j, 0, 2 * n){
            cin >> worker[i][j];
        }
    }
    vvi station(n, vi(2 * n));
    rep(i, 0, n){
        rep(j, 0, 2 * n){
            cin >> station[i][j];
        }
    }
    int bestpref = -1, score = INT_MAX;
    vi works(n), stats(n);
    rep(pref, 0, n + 1){
        vvi costs(n, vi(n, 1e7));
        rep(i, 0, n){
            rep(j, 0, n){
                costs[i][j] = worker[i][2 * j + (j >= pref)];
            }
        }
        auto [sc1, ws] = hungarian(costs);
        rep(i, 0, n){
            rep(j, 0, n){
                costs[i][j] = station[i][2 * j + (j >= pref)];
            }
        }
        auto [sc2, ss] = hungarian(costs);
        sc1 += sc2;
        // cout << pref << " " << sc1 << nL;
        if(sc1 < score){
            score = sc1;
            bestpref = pref;
            works = ws;
            stats = ss;
        }
    }
    cout << score << nL;
    vi statwork(n);
    rep(i, 0, n){
        rep(j, 0, n){
            if(works[i] == stats[j]) statwork[i] = j;
        }
    }
    rep(i, 0, n){
        cout << (i + 1) << " " << (works[i] + 1) << "" << (works[i] >= bestpref ? 'B' : 'A') << " " << (statwork[i] + 1) << nL;
    }
    
    return 0;
}
