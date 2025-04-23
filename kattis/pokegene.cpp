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

struct Node;
vector<Node> trie;
struct Node {
    vi c;
    Node() : c(26, -1){}
};
int add(int cur, string &s, int idx) {
    if(idx == sz(s)) return cur;
    int i = s[idx]-'a';
    if(trie[cur].c[i] == -1) {
        trie[cur].c[i] = sz(trie);
        trie.push_back(Node());
    }
    return add(trie[cur].c[i], s, idx+1);
}

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
	vi time, path, ret, p, dep;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), p(sz(C), -1), dep(sz(C), 0), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
            p[y] = v;
            dep[y] = dep[v]+1;
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

vii compressTree(LCA& lca, const vi& subset) {
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
	vii ret = {pii(0, li[0])};
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
    int n, q; cin >> n >> q;
    trie.push_back(Node());
    vi w;
    rep(i, 0, n){
        string s; cin >> s;
        w.pb(add(0, s, 0));
    }
    vvi adj(sz(trie));
    rep(i, 0, sz(adj)) {
        for(int j : trie[i].c){
            if(j == -1) continue;
            adj[i].pb(j);
        }
    }
    LCA lca(adj);
    rep(qid, 0, q) {
        int k, l; cin >> k >> l;
        vi sub(k);
        rep(i, 0, k) {
            cin >> sub[i]; sub[i]--;
            sub[i] = w[sub[i]];
        }
        sort(all(sub));
        vii comp = compressTree(lca, sub);
        vvi child(sz(comp));
        rep(i, 1, sz(comp)) {
            child[comp[i].first].pb(i);
        }
        int ans = 0;
        auto dfs = [&](int u, auto &&dfs) -> int {
            int o = comp[u].second;
            int sum = 0;
            auto it = lower_bound(all(sub), o);
            if(it != end(sub) && *it == o) sum++;
            for(int v : child[u]) {
                sum += dfs(v, dfs);
            }
            if(sum == l) {
                if(u == 0) {
                    ans += lca.dep[o];
                } else {
                    ans += lca.dep[o];
                    ans -= lca.dep[comp[comp[u].first].second];
                }
            }
            return sum;
        };
        dfs(0, dfs);
        cout << ans << "\n";
    }
    
    return 0;
}
