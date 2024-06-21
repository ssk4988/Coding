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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi adj(n);
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    LCA lc(adj);
    int lg = __lg(n);
    vi tin(n), tout(n), depth(n), par(n);
    int T = 0;
    vvi jmp(lg+1, vi(n));
    int n2 = 2 * (lg + 1) - 1;
    // 0, +1,... +lg, -1, ..., -lg
    // 0, push down to range, pull up from range
    vvi pwadj(n2 * n);
    auto anc = [&](int u, int a) -> bool { return a == -1 || (u != -1 && tin[a] <= tin[u] && tout[u] <= tout[a]); };
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        tin[u] = T++;
        par[u] = p;
        jmp[0][u] = p;
        rep(pw, 1, lg+1){
            jmp[pw][u] = jmp[pw-1][u] == -1 ? -1 : jmp[pw-1][jmp[pw-1][u]];
            pwadj[pw * n + u].pb((pw-1) * n + u);
            if(jmp[pw-1][u] != -1) pwadj[pw * n + u].pb((pw-1) * n + jmp[pw-1][u]);
            int o = pw == 1 ? pw-1 : pw + lg - 1;
            pwadj[o * n + u].pb((pw+lg) * n + u);
            if(jmp[pw-1][u] != -1) pwadj[o * n + jmp[pw-1][u]].pb((pw+lg) * n + u);
        }
        for(int v : adj[u]){
            if(v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u, dfs);
        }
        tout[u] = T;
    };
    dfs(0, -1, dfs);
    rep(i, 0, n){
        // cout << i << " " << depth[i] << "\n";
        rep(j, 0, lg+1){
            // cout << i << " " << j << " " << jmp[j][i] << "\n";
        }
    }
    auto label = [&](int t, int u, int avoid, int target) -> void {
        // cout << "label " << t << " " << u << " " << avoid << " " << target << "\n";

        for(int p = lg; p >= 0; p--) {
            if(u != -1 && anc(jmp[p][u], avoid)){
                // cout << "level " << p << "," << u << "\n";
                if(t == 1) {
                    pwadj[target].pb(p * n + u);
                } else {
                    pwadj[(p + lg) * n + u].pb(target);
                }
                u = jmp[p][u];
            }
        }
    };
    rep(q, 0, m){
        int t, a, b, c; cin >> t >> a >> b >> c; a--, b--, c--;
        int l = lc.lca(a, b);
        if(a == b) continue;
        // cout << "query " << q << ":\n";
        if(l == a || l == b) {
            if(l == b) swap(a, b);
            // l == a
            label(t, b, c, c);
            if(par[c] != -1) label(t, par[c], par[a], c);
        } else if(l == c) {
            label(t, a, c, c);
            label(t, b, c, c);
        } else {
            if(anc(b, c)) {
                swap(a, b);
            }
            label(t, a, c, c);
            label(t, b, par[l], c);
            if(par[c] != -1) label(t, par[c], par[l], c);
        }
    }
    vi state(n2 * n);
    vi ts;
    auto topsort = [&](int u, auto &&topsort) -> bool {
        // cout << "visit " << u << " " << state[u] << " " << u/n << "," << u%n << "\n";
        if(state[u]) return state[u] == 1;
        state[u] = 1;
        for(int v : pwadj[u]) {
            if(topsort(v, topsort)) return true;
        }
        state[u] = 2;
        if(u < n) ts.pb(u);
        return false;
    };
    bool works = true;
    rep(i, 0, n) 
        if(topsort(i, topsort)) {
            works = false;
            break;
        }
    if(!works){
        cout << -1 << "\n";
    }
    else {
        vi ans(n);
        reverse(all(ts));
        rep(i, 0, n){
            // cout << ts[i] << "\n";
            ans[ts[i]] = i;
        }
        rep(i, 0, n){
            cout << ans[i]+1 << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
