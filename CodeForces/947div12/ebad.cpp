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

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0, val = 0;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = l->val + r->val;
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		push();
		return l->query(L, R) + r->query(L, R);
	}
	// void set(int L, int R, int x) {
	// 	if (R <= lo || hi <= L) return;
	// 	if (L <= lo && hi <= R) mset = val = x, madd = 0;
	// 	else {
	// 		push(), l->set(L, R, x), r->set(L, R, x);
	// 		val = max(l->val, r->val);
	// 	}
	// }
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = l->val + r->val;
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		// if (mset != inf)
		// 	l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		// else 
        if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

template <bool VALS_EDGES> struct HLD {
	int N, tim = 0;
	vector<vi> adj;
	vi par, siz, depth, rt, pos;
	Node *tree;
	HLD(vector<vi> adj_)
		: N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1), depth(N),
		  rt(N),pos(N),tree(new Node(0, N)){ dfsSz(0); dfsHld(0); }
	void dfsSz(int v) {
		if (par[v] != -1) adj[v].erase(find(all(adj[v]), par[v]));
		for (int& u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(int u, int v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			op(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void modifyPath(int u, int v, int val) {
		process(u, v, [&](int l, int r) { tree->add(l, r, val); });
	}
	int queryPath(int u, int v) { // Modify depending on problem
		int res = 0;
		process(u, v, [&](int l, int r) {
				res = res + tree->query(l, r);
		});
		return res;
	}
	int querySubtree(int v) { // modifySubtree is similar
		return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, q; cin >> n >> q;
        vvi adj(n);
        vi c(n);
        rep(i, 0, n){
            cin >> c[i];
        }
        rep(i, 0, n-1){
            int a, b; cin >> a >> b; a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        int T = 0;
        vi time(n), time1(n);
        vi invtime(n);
        vi par(n, -1);
        auto dfs = [&](int u, int p, vi&t, auto &&dfs) -> void {
            par[u] = p;
            for(int v : adj[u]){
                if(v == p) continue;
                dfs(v, u, t, dfs);
            }
            t[u] = T++;
        };
        dfs(0, -1, time, dfs);
        T = 0;
        rep(i, 0, n){
            invtime[time[i]] = i;
            reverse(all(adj[i]));
        }
        dfs(0, -1, time1, dfs);
        vi invtime1(n);
        rep(i, 0, n){
            invtime1[time1[i]] = i;
        }
        set<int> bon, bon1;
        HLD<0> h(adj);
        HLD<0> p(adj);
        auto add = [&](int u) -> void {
            c[u] = 1;
            bon.insert(time[u]);
            bon1.insert(time1[u]);
            h.modifyPath(u, u, 1);
        };
        auto rem = [&](int u) -> void {
            c[u] = 0;
            bon.erase(time[u]);
            bon1.erase(time1[u]);
            h.modifyPath(u, u, -1);
        };
        rep(i, 0, n){
            if(c[i]) {
                add(i);
            }
            p.modifyPath(i, i, 1);
        }
        rep(i, 0, q){
            int x; cin >> x; x--;
            if(c[x]){
                rem(x);
            } else{
                add(x);
            }
            if(sz(bon) == 0) {
                cout << "NO\n";
                continue;
            }
            if(sz(bon) == 1){
                cout << "YES\n";
                continue;
            }
            int l = invtime[*bon.begin()], top = invtime[*prev(bon.end())];
            int l2 = invtime1[*bon1.begin()];
            // cout << "path to " << l << " lca" << top << " " << l2 << "\n";
            int sum = h.queryPath(l, l == l2 ? top : l2);
            int dist = p.queryPath(l, l == l2 ? top : l2);
            // cout << "sum: " << sum << "\n";
            cout << (sum == dist && sum == sz(bon) ? "YES" : "NO") << "\n";
        }

    }
    
    return 0;
}
