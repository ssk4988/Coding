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

typedef vector<bitset<75>> vb;
struct Maxclique {
	double limit=0.025, pk=0;
	struct Vertex { int i, d=0; };
	typedef vector<Vertex> vv;
	vb e;
	vv V;
	vector<vi> C;
	vi qmax, q, S, old;
	void init(vv& r) {
		for (auto& v : r) v.d = 0;
		for (auto& v : r) for (auto j : r) v.d += e[v.i][j.i];
		sort(all(r), [](auto a, auto b) { return a.d > b.d; });
		int mxD = r[0].d;
		rep(i,0,sz(r)) r[i].d = min(i, mxD) + 1;
	}
	void expand(vv& R, int lev = 1) {
		S[lev] += S[lev - 1] - old[lev];
		old[lev] = S[lev - 1];
		while (sz(R)) {
			if (sz(q) + R.back().d <= sz(qmax)) return;
			q.push_back(R.back().i);
			vv T;
			for(auto v:R) if (e[R.back().i][v.i]) T.push_back({v.i});
			if (sz(T)) {
				if (S[lev]++ / ++pk < limit) init(T);
				int j = 0, mxk = 1, mnk = max(sz(qmax) - sz(q) + 1, 1);
				C[1].clear(), C[2].clear();
				for (auto v : T) {
					int k = 1;
					auto f = [&](int i) { return e[v.i][i]; };
					while (any_of(all(C[k]), f)) k++;
					if (k > mxk) mxk = k, C[mxk + 1].clear();
					if (k < mnk) T[j++].i = v.i;
					C[k].push_back(v.i);
				}
				if (j > 0) T[j - 1].d = 0;
				rep(k,mnk,mxk + 1) for (int i : C[k])
					T[j].i = i, T[j++].d = k;
				expand(T, lev + 1);
			} else if (sz(q) > sz(qmax)) qmax = q;
			q.pop_back(), R.pop_back();
		}
	}
	vi maxClique() { init(V), expand(V); return qmax; }
	Maxclique(vb conn) : e(conn), C(sz(e)+1), S(sz(C)), old(S) {
		rep(i,0,sz(e)) V.push_back({i});
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vb adj(n);
    rep(i, 0, n){
        string s; cin >> s;
        rep(j, 0, n){
            adj[i][j] = s[j] == 'Y';
        }
    }
    vb protect(n);
    auto dfs = [&](int u, int source, auto &&dfs) -> void {
        if(protect[source][u]) return;
        protect[source][u] = true;
        rep(v, 0, n){
            if(adj[u][v]) dfs(v, source, dfs);
        }
    };
    rep(i, 0, n){
        rep(j, 0, n) if(adj[i][j]) dfs(j, i, dfs);
    }
    vi bad(n);
    rep(i, 0, n){
        rep(j, 0, n){
            if(protect[i][j] && protect[j][i]) bad[i] = bad[j] = true;
        }
    }
    int numbad = accumulate(all(bad), 0);
    if(numbad == n){
        cout << 0 << "\n";
        return 0;
    }
    vb inv(n);
    rep(i, 0, n){
        if(bad[i]) continue;
        rep(j, i+1, n){
            if(bad[j]) continue;
            if(!protect[i][j] && !protect[j][i]) inv[i][j] = inv[j][i] = 1;
        }
    }
    auto x = Maxclique(inv).maxClique();
    cout << sz(x) << "\n";



    return 0;
}
