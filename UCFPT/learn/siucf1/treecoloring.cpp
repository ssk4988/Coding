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
	vi time, path, ret, par;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), par(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int p) {
		time[v] = T++;
        par[v] = p;
		for (int y : C[v]) if (y != p) {
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

using F = int;
using S = pii;
S op(S a, S b) { return {a.f + b.f, a.s + b.s}; }
S ego() { return {0, 0}; }
F id() { return 0; }
F composition(F a, F b) {
    return a + b;
}
S mapping(F f, S s) {
    return {s.f + f * s.s, s.s};
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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, q, k; cin >> n >> q >> k;
        vvi adj(n);
        rep(i, 1, n) {
            int p; cin >> p; p--;
            adj[i].pb(p);
            adj[p].pb(i);
        }
        LCA lca(adj);
        vi a(n);
        rep(i, 0, n) {
            cin >> a[i]; a[i]--;
        }
        int T = 0;
        vi tin(n), subsz(n, 1);
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            tin[u] = T++;
            for(int v : adj[u]) if(v != p) {
                dfs(v, u, dfs);
                subsz[u] += subsz[v];
            }
        };
        dfs(0, -1, dfs);
        vector<Tree> subtrees(k, Tree(n));
        vector<Tree> pathtrees(k, Tree(n));
        rep(i, 0, n) {
            rep(j, 0, k) {
                subtrees[j].set(i, {0, 1});
                pathtrees[j].set(i, {0, 1});
            }
        }
        rep(i, 0, n) {
            subtrees[a[i]].apply(tin[i], tin[i]+1, 1);
            pathtrees[a[i]].apply(tin[i], tin[i]+subsz[i], 1);
        }
        rep(qid, 0, q) {
            int t; cin >> t;
            if(t == 1) {
                int u, c; cin >> u >> c; u--, c--;
                subtrees[a[u]].apply(tin[u], tin[u]+1, -1);
                pathtrees[a[u]].apply(tin[u], tin[u]+subsz[u], -1);
                a[u] = c;
                pathtrees[a[u]].apply(tin[u], tin[u]+subsz[u], 1);
                subtrees[a[u]].apply(tin[u], tin[u]+1, 1);
            } else if(t == 2) {
                int u; cin >> u; u--;
                pair<int, vi> mx = {-1, {}};
                rep(i, 0, k) {
                    int v = subtrees[i].prod(tin[u], tin[u] + subsz[u]).f;
                    if(v > mx.f) mx.s.clear();
                    if(v >= mx.f) {
                        mx.f = v;
                        mx.s.pb(i);
                    }
                }
                for(int v : mx.s) {
                    cout << v+1 << " ";
                }
                cout << "\n";
            } else {
                int u, v; cin >> u >> v; u--, v--;
                int l = lca.lca(u, v);
                int p = lca.par[l];
                pair<int, vi> mx = {-1, {}};
                rep(i, 0, k) {
                    int w = pathtrees[i].prod(tin[u], tin[u]+1).f + pathtrees[i].prod(tin[v], tin[v]+1).f
                        - pathtrees[i].prod(tin[l], tin[l]+1).f;
                    if(p != -1) w -= pathtrees[i].prod(tin[p], tin[p]+1).f;
                    if(w > mx.f) mx.s.clear();
                    if(w >= mx.
                        f) {
                        mx.f = w;
                        mx.s.pb(i);
                    }
                }
                for(int i : mx.s) cout << i+1 << " ";
                cout << "\n";
            }
        }
    }
    
    
    return 0;
}
