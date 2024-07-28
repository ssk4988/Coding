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

vpi compressTree(LCA& lca, const vi& subset) {
	static vi rev; rev.resize(sz(lca.time));
	vi li = subset, &T = lca.time;
	auto cmp = [&](int a, int b) { return T[a] < T[b]; };
	sort(all(li), cmp);
	int m = sz(li)-1;
	rep(i,0,m) {
		int a = li[i], b = li[i+1];
		li.push_back(lca.lca(a, b));
	}
	sort(all(li), cmp);
	li.erase(unique(all(li)), li.end());
	rep(i,0,sz(li)) rev[li[i]] = i;
	vpi ret = {pi(0, li[0])};
	rep(i,0,sz(li)-1) {
		int a = li[i], b = li[i+1];
		ret.emplace_back(rev[lca.lca(a, b)], b);
	}
	return ret;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<set<int>> adjset(n);
    rep(i, 0,n){
        adjset[i] = set<int>(all(adj[i]));
    }
    LCA lca(adj);
    int q; cin >> q;
    vi issub(n);
    rep(_, 0, q){
        int k; cin >> k;
        vi sub(k);
        rep(i, 0, k){
            cin >> sub[i];
            sub[i]--;
            issub[sub[i]] = 1;
        }
        vpi tree = compressTree(lca, sub);
        int m = sz(tree);
        vvi vadj(m);
        vi imp(m);
        rep(i, 0, m){
            auto [par, orig] = tree[i];
            imp[i] = issub[orig];
            if(i) vadj[par].pb(i);
        }
        int ans = 0;
        auto dfs = [&](int u, int p, auto &&dfs) -> int {
            int cnt = 0;
            for(int v : vadj[u]) {
                if(v == p) continue;
                int t = dfs(v, u, dfs);
                if(t) {
                    if(imp[u] && (!imp[v] || imp[v] && !adjset[tree[u].s].count(tree[v].s))){
                        ans++;
                    } else cnt += t;
                }
                if(imp[u] && imp[v] && adjset[tree[u].s].count(tree[v].s)) ans = -1e9;
            }
            if(cnt >= 2){
                ans++;
                cnt = 0;
            }
            if(cnt || imp[u]) cnt = 1;
            return cnt;
        };
        dfs(0, 0, dfs);
        for(int i : sub) issub[i] = 0;
        if(ans < 0) cout << -1 << "\n";
        else cout << ans << "\n";
    }
    
    return 0;
}
