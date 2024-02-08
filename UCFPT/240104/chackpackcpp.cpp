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

// https://codeforces.com/blog/entry/75885
struct SplayTree {
	struct Node {
		int ch[2] = {0, 0}, p = 0, cnt = 1;
		ll self = 0, path = 0; // Path aggregates
		ll sub = 0, vir = 0; // Subtree aggregates
		bool flip = 0; // Lazy tags
	};
	vector<Node> T;
	SplayTree(int n): T(n + 1) { T[0].cnt = 0; }
	void push(int x) {
		if (!x || !T[x].flip) return;
		int l = T[x].ch[0], r = T[x].ch[1];
		T[l].flip ^= 1, T[r].flip ^= 1;
		swap(T[x].ch[0], T[x].ch[1]);
		T[x].flip = 0;
	}
	void pull(int x) {
		int l = T[x].ch[0], r = T[x].ch[1];
		push(l);
		push(r);
		T[x].path = T[l].path + T[x].self + T[r].path;
		T[x].sub = T[x].vir + T[l].sub + T[r].sub + T[x].self;
		T[x].cnt = T[l].cnt + 1 + T[r].cnt;
	}
	void set(int x, int d, int y) {
		T[x].ch[d] = y;
		T[y].p = x;
		pull(x);
	}
	void splay(int x) {
		auto dir = [&](int x) {
			int p = T[x].p;
			if (!p) return -1;
			return T[p].ch[0] == x ? 0 : T[p].ch[1] == x ? 1 : -1;
		};
		auto rotate = [&](int x) {
			int y = T[x].p, z = T[y].p, dx = dir(x), dy = dir(y);
			set(y, dx, T[x].ch[!dx]);
			set(x, !dx, y);
			if (~dy) set(z, dy, x);
			T[x].p = z;
		};
		for (push(x); ~dir(x);) {
			int y = T[x].p, z = T[y].p;
			push(z);
			push(y);
			push(x);
			int dx = dir(x), dy = dir(y);
			if (~dy) rotate(dx != dy ? x : y);
			rotate(x);
		}
	}
};
 
// https://codeforces.com/blog/entry/75885
struct LinkCut: SplayTree {
	LinkCut(int n): SplayTree(n) {}
	int access(int x) {
		int u = x, v = 0;
		for (; u; v = u, u = T[u].p) {
			splay(u);
			int& ov = T[u].ch[1];
			T[u].vir += T[ov].sub;
			T[u].vir -= T[v].sub;
			ov = v;
			pull(u);
		}
		return splay(x), v;
	}
	void reroot(int x) {
		access(x);
		T[x].flip ^= 1;
		push(x);
	}
	void Link(int u, int v) {
		reroot(u), access(v);
		T[v].vir += T[u].sub;
		T[u].p = v;
		pull(v);
	}
	void Cut(int u, int v) {
		reroot(u), access(v);
		T[v].ch[0] = T[u].p = 0;
		pull(v);
	}
	// Rooted tree LCA. Returns 0 if u and v arent connected.
	int LCA(int u, int v) {
		if (u == v) return u;
		access(u);
		int ret = access(v);
		return T[u].p ? ret : 0;
	}
	// Query subtree of u where v is outside the subtree.
	ll Subtree(int u, int v) {
		reroot(v), access(u);
		return T[u].vir + T[u].self;
	}
	// Query path [u..v]
	ll Path(int u, int v) {
		reroot(u), access(v);
		return T[v].path;
	}
	// Update vertex u with value v
	void Update(int u, ll v) {
		access(u);
		T[u].self = v;
		pull(u);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vi a(n);
        set<int> unused;
        LinkCut tree(n + 2);
        rep(i, 0, n){
            cin >> a[i]; a[i];
        }
        int sink = n + 1;
        rep(i, 0, n + 1){
            unused.insert(i);
            tree.Link(i+1, i+1 + 1);
        }
        vi ans;
        rep(i, 0, n){
            while(sz(unused)){
                auto it = unused.lower_bound(a[i]);
                if(it == unused.begin()) break;
                it = prev(it);
                int val = *it;
                if(val + k < a[i]) break;
                tree.Cut(val+1, val+1 + 1);
                tree.Update(val+1, 1);
                tree.Link(val+1, min(n, val + k)+1);
				tree.reroot(sink+1);
                unused.erase(val);
            }
            ans.pb(tree.Path(0+1, sink+1));
        }
        for(int i : ans) cout << i << " ";
        cout << "\n";
    }
    
    return 0;
}
