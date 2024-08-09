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
	vi time, path, ret, depth;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), depth(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
            depth[y] = depth[v] + 1;
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	int dist(int a, int b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

struct Node {
	int lo, hi;
	Node *l = 0, *r = 0;
	int val = 0, lz = 0;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if(lo + 1 < hi){
			int mid = lo + (hi - lo) / 2;
			l = new Node(lo, mid), r = new Node(mid, hi);
		}
	}
	int query(int idx) {
		if(lo + 1 == hi) {
			return val;
		}
		push();
		int mid = lo + (hi - lo) / 2;
		if(mid <= idx) return r->query(idx);
		else return l->query(idx);
	}
	void upd(int L, int R, int v) {
		if(R <= lo || hi <= L) return;
		if(L <= lo && hi <= R) {
			val ^= v;
			lz ^= v;
			return;
		}
		push();
		l->upd(L, R, v), r->upd(L, R, v);
	}
	void push(){
		if(lz) l->upd(lo, hi, lz), r->upd(lo, hi, lz), lz = 0;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vvi adj(n);
	vi v(n);
	rep(i, 0, n) cin >> v[i];
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    LCA lca(adj);
	vi subsz(n, 1);
	vi tin(n);
	int T = 0;
	auto dfs = [&](int u, int p, auto &&dfs) -> void {
		tin[u] = T++;
		for(int v : adj[u]) if(v != p){
			dfs(v, u, dfs);
			subsz[u] += subsz[v];
		}
	};
	dfs(0, -1, dfs);
    Node tree(0, n);
	rep(i, 0, n){
		tree.upd(tin[i], tin[i] + subsz[i], v[i]);
	}
	rep(i, 0, q){
		int t, a, b; cin >> t >> a >> b; a--, b--;
		if(t == 1){
			b++;
			tree.upd(tin[a], tin[a] + subsz[a], v[a] ^ b);
			v[a] = b;
		} else {
			int l = lca.lca(a, b);
			int ans = tree.query(tin[a]) ^ tree.query(tin[b]) ^ v[l];
			cout << ans << "\n";
		}
	}

    
    return 0;
}
