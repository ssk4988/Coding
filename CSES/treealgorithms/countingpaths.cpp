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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    LCA lca(adj);
    vi subsz(n, 1);
    vi marked(n);
    vi par(n);
    auto dfs = [&](int cur, int pre, auto &&dfs)->void{
        par[cur] = pre;
        for(int i : adj[cur]){
            if(i == pre) continue;
            dfs(i, cur, dfs);
            subsz[cur] += subsz[i];
        }
    };
    dfs(0, -1, dfs);
    rep(i, 0, q){
        int a, b; cin >> a >> b;
        a--,b--;
        int lc = lca.lca(a, b);
        marked[a]++, marked[b]++, marked[lc]--;
        if(lc != 0) marked[par[lc]]--;
    }
    auto dfs1 = [&](int cur, int pre, auto &&dfs1)->void{
        for(int i : adj[cur]){
            if(i == pre) continue;
            dfs1(i, cur, dfs1);
            marked[cur] += marked[i];
        }
    };
    dfs1(0, -1, dfs1);
    vl ans(n, 0);
    rep(i, 0, n){
        cout << marked[i] << " ";
    }
    cout << nL;
    
    return 0;
}