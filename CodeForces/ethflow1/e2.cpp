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
vvi tmp(1);
LCA lca(tmp);

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a+b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

struct TreeLCA {
	typedef int T;
	static constexpr T unit = -1;
	T f(T a, T b) { 
        if(a >= 0 && b >= 0) return lca.lca(a, b);
        if(a >= 0) return a;
        return b;
    } // (any associative fn)
	vector<T> s; int n;
	TreeLCA(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

// calculate for each node the nodes with greater w outside subtree and lca of all such
// node wins if outside greater nodes have no options - all nodes have an lca in this subtree or not at all

// bad0: contains all nodes with greater w than it
// good1: only nodes with greater w outside it are bad0
// good1req: also calc lca of those such nodes
// bad1: exists good outside it with greater w that does not depend on its subtree (lca of good1req is not in its subtree)
// good2: only nodes with greater w outside it are bad0 or bad1

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi w(n);
        vvi bucket(n);
        rep(i, 0, n){
            cin >> w[i]; w[i]--;
            bucket[w[i]].pb(i);
        }
        vi good(n);
        vvi adj(n);
        rep(i, 0, n-1){
            int u, v; cin >> u >> v; u--, v--;
            adj[u].push_back(v);adj[v].pb(u);
        }
        lca = LCA(adj);
        int T = 0;
        vi tin(n), subsz(n, 1);
        auto dfs = [&](int u,int p, auto &&dfs) -> void {
            tin[u] = T++;
            for(int v : adj[u]) if(v != p) {
                dfs(v, u, dfs);
                subsz[u] += subsz[v];
            }
        };
        dfs(0, -1, dfs);
        TreeLCA lct(n);
        vi lcaother(n, -1);
        for(int i = n-1; i >= 0; i--) {
            for(int u : bucket[i]) {
                lcaother[u] = lct.f(lct.query(0, tin[u]), lct.query(tin[u]+subsz[u], n));
            }
            for(int u : bucket[i]) {
                lct.update(tin[u], u);
            }
        }

        Tree activetree(n), cnttree(n);
        for(int i = n-1; i >= 0; i--) {
            for(int u : bucket[i]) {
                int othercnt = cnttree.query(0, tin[u]) + cnttree.query(tin[u] + subsz[u], n);
                int otheruse = activetree.query(0, tin[u]) + activetree.query(tin[u] + subsz[u], n);
                if(otheruse == 0 && othercnt){
                    good[u] = 1;
                }
            }
            for(int u : bucket[i]) {
                if(lcaother[u] != -1) activetree.update(lcaother[u], 1);
                cnttree.update(tin[u], 1);
            }
        }
        vi ans;
        rep(u, 0, n) {
            if(good[u]) ans.pb(u);
        }
        sort(all(ans));
        cout << sz(ans) << " ";
        for(int v : ans) cout << v+1 << " ";
        cout << "\n";
    }
    
    return 0;
}
