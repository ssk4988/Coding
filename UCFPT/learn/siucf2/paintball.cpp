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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct S {
    array<ll, 3> ans{0, 0, 0};
    array<ll, 2> side{0, 0}; // length of edge on left/right
    array<int, 2> col{0, 0}; // color of edge on left/right
    ll len=0; // length of entire
};
S ego() {
    return S();
}
S makeS(ll l, int c) {
    S res = ego();
    rep(i, 0, 3) {
        if(i == c) res.ans[i] = l;
        else res.ans[i] = l * l;
    }
    res.side = {l, l};
    res.col = {c, c};
    res.len = l;
    return res;
}
S rev(S s) {
    swap(s.side[0], s.side[1]);
    swap(s.col[0], s.col[1]);
    return s;
}
S op(S a, S b) {
    if(a.len==0 || b.len==0) return a.len==0 ? b : a;
    rep(i, 0, 3) a.ans[i] += b.ans[i];
    if(a.col[1] == b.col[0]) {
        rep(i, 0, 3) {
            if(i == a.col[1]) continue;
            a.ans[i] += 2 * a.side[1] * b.side[0];
        }
        if(a.side[0] == a.len) {
            a.side[0] += b.side[0];
        }
        if(b.side[0] == b.len) {
            a.side[1] += b.side[0];
        } else {
            a.side[1] = b.side[1];
        }
    }
    else {
        a.side[1] = b.side[1];
    }
    a.col[1] = b.col[1];
    a.len += b.len;
    return a;
}
using F = int;
F id() { return -1; }
S mapping(F f, S s) {
    if (f==id()) return s;
    s.side[0] = s.side[1] = s.len;
    s.col[0] = s.col[1] = f;
    rep(i, 0, 3) {
        if(i == f) s.ans[i] = s.len;
        else s.ans[i] = s.len * s.len;
    }
    return s;
}

F composition(F newer, F older) {
    if(newer==id()) return older;
    return newer;
}

struct Tree {
	int n, size, log;
	vector<S> d;
	vector<F> lz;
	Tree(size_t m) {
        size = 1;
        while(size < m) size *= 2;
		n = m; log = __lg(size);
		d = vector(2*size, ego());
		lz = vector(size, id());
	}
	void update(int k) { d[k] = op(d[2*k], d[2*k + 1]); }
	void fid(int k, F f) {
		d[k] = mapping(f, d[k]);
		if (k < size) lz[k] = composition(f, lz[k]);
	}
	void push(int k) {
		fid(2 * k, lz[k]);
		fid(2 * k + 1, lz[k]);
		lz[k] = id();
	}
	#define tip for (int i = 1; i <= log; i++)
	#define dip for (int i = log; i >= 1; i--)
	#define check(p) { if (((1<<i)-1) & l) p(l >> i);\
	                   if (((1<<i)-1) & r) p((r-1) >> i); }
	void set(int p, S x) {
		p += size;
		dip push(p >> i);
		d[p] = x;
		tip update(p >> i);
	}
	S prod(int l, int r) {
        assert(l <= r);
		l += size; r += size;
		dip check(push);
		S sml = ego(); S smr = ego();
		while (l < r) {
			if (l & 1) sml = op(sml, d[l++]);
			if (r & 1) smr = op(d[--r], smr);
			l /= 2, r /= 2;
		}
		return op(sml, smr);
	}
	void apply(int l, int r, F f) {
		l += size; r += size;
		int l2 = l, r2 = r;
		dip check(push);
		while (l < r) {
			if (l & 1) fid(l++, f);
			if (r & 1) fid(--r, f);
			l /= 2, r /= 2;
		}
		l = l2; r = r2;
		tip check(update);
	}
};

template <bool VALS_EDGES> struct HLD {
	int N, tim = 0;
	vector<vi> adj;
	vi par, siz, rt, pos;
	Tree tree;
	HLD(vector<vi> adj_)
		: N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1),
		  rt(N),pos(N),tree(N){ dfsSz(0); dfsHld(0); 
            // cerr << "\n";
        }
	void dfsSz(int v) {
		for (int& u : adj[v]) {
			adj[u].erase(find(all(adj[u]), v));
			par[u] = v;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++;
        // cerr << v << " ";
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(int u, int v, B op) {
		for (;; v = par[rt[v]]) {
			if (pos[u] > pos[v]) swap(u, v);
			if (rt[u] == rt[v]) break;
			op(pos[rt[v]], pos[v] + 1);
		}
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void modifyPath(int u, int v, int val) {
		process(u, v, [&](int l, int r) { tree.apply(l, r, val); });
	}
	S queryPath(int u, int v) { // Modify depending on problem
        // cerr << "query " << u << " to " << v << endl;
		S left=ego(), right=ego();
        while(true) {
            if(rt[u] == rt[v]) break;
            if(pos[u] > pos[v]) {
                // S b = tree.prod(pos[rt[u]], pos[u]+1);
                left = op(left, rev(tree.prod(pos[rt[u]], pos[u]+1)));
                // cerr << "left " << pos[rt[u]] << "," << pos[u]+1 << endl;
                u = par[rt[u]];
            } else {
                right = op(tree.prod(pos[rt[v]], pos[v]+1), right);
                // cerr << "right " << pos[rt[v]] << "," << pos[v]+1 << endl;
                v = par[rt[v]];
            }
        }
        bool flag = false;
        if(pos[u] > pos[v]) swap(u, v), flag = true;
        // cerr << "mid " << pos[u]+VALS_EDGES << " " << pos[v]+1 << endl;
        S mid = tree.prod(pos[u]+VALS_EDGES, pos[v]+1);
        if(flag) mid = rev(mid);
		return op(left, op(mid, right));
	}
};

int colid(char c){
    if(c=='B') return 0;
    if(c == 'G') return 1;
    return 2;
}

void solve() {
    int n; cin >> n;
    vector<array<int, 3>> ed(n-1);
    vi col(n-1);
    vvi adj(n);
    rep(i, 0, n-1) {
        rep(j, 0, 3) cin >> ed[i][j];
        ed[i][0]--, ed[i][1]--;
        char c; cin >> c; col[i] = colid(c);
        auto [u, v, l] = ed[i];
        adj[u].pb(v);
        adj[v].pb(u);
    }
    HLD<1> hld(adj);
    rep(i, 0, n-1) {
        auto [u,v,len] = ed[i];
        int r = u == hld.par[v] ? u : v;
        int t = r == u ? v : u;
        auto c = col[i];
        hld.tree.set(hld.pos[t], makeS(len, c));
    }
    int q; cin >> q;
    rep(i, 0, q) {
        int t; cin >> t;
        if(t == 1) {
            int u, v; char c; cin >> u >> v >> c; u--, v--;
            S res = hld.queryPath(u, v);
            ll ans = res.ans[colid(c)];
            cout << ans << "\n";
            // cout << ans << " c=" << colid(c) << " ";
            // rep(j, 0, 3) cout << res.ans[j] << " ";
            // cout << "\n";
        } else if (t == 2) {
            int u, v; char c; cin >> u >> v >> c; u--, v--;
            hld.modifyPath(u, v, colid(c));
        } else {
            int id; ll len; cin >> id >> len; id--;
            auto [u,v,l1] = ed[id];
            int r = u == hld.par[v] ? u : v;
            int t = r == u ? v : u;
            S res = hld.queryPath(u, v);
            int c = res.col[0];
            assert(res.len == res.side[0]);
            hld.tree.set(hld.pos[t], makeS(len, c));
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int nc; cin >> nc;
    rep(cn, 0, nc) solve();
    
    return 0;
}
