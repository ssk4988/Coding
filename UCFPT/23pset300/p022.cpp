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

const int N = 1e3 + 10;
vi g[N];
vi rg[N], bucket[N];
int sdom[N], par[N], dom[N], dsu[N], label[N];
int arr[N], rev[N], T;
int Find(int u, int x = 0)
{
    if (u == dsu[u])
        return x ? -1 : u;
    int v = Find(dsu[u], x + 1);
    if (v < 0)
        return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]])
        label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
}
void Union(int u, int v) // Add an edge u-->v
{
    dsu[v] = u; // yup,its correct :)
}
void dfs0(int u)
{
    T++;
    arr[u] = T;
    rev[T] = u;
    label[T] = T;
    sdom[T] = T;
    dsu[T] = T;
    for (int i = 0; i < sz(g[u]); i++)
    {
        int w = g[u][i];
        if (!arr[w])
            dfs0(w), par[arr[w]] = arr[u];
        rg[arr[w]].pb(arr[u]);
    }
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
    int n, k;
    cin >> n >> k;
    rep(i, 0, k){
        int v; cin >> v;
        rep(j, 0, v){
            int a; cin >> a;
            g[a].pb(i + 1);
        }
    }
    // node n + 1 is new root, above regular nurses
    rep(i, k + 1, n + 1){
        g[n + 1].pb(i);
    }
    dfs0(n + 1);
    vi vacation(n + 1);
    rep(i, 1, n + 1){
        if(arr[i]) vacation[i] = true;
    }
    for (int i = T; i > 0; i--)
    {
        // if(!vacation[i]) continue; // should always have vacation since we dfs'd from regular nurses
        for (int j = 0; j < sz(rg[i]); j++)
            sdom[i] = min(sdom[i], sdom[Find(rg[i][j])]);
        if (i > 1)
            bucket[sdom[i]].pb(i);
        for (int j = 0; j < sz(bucket[i]); j++)
        {
            int w = bucket[i][j];
            int v = Find(w);
            if (sdom[v] == sdom[w])
                dom[w] = sdom[w];
            else
                dom[w] = v;
        }
        if (i > 1)
            Union(par[i], i);
    }
    vi tree(T);
    vvi child(T);
    for (int i = 2; i <= T; i++)
    {
        if (dom[i] != sdom[i])
            dom[i] = dom[dom[i]];
        tree[i - 1] = dom[i] - 1; // remember to revlabel at end
        child[dom[i] - 1].pb(i - 1);
    }
    tree[0] = 0;
    LCA lc(child);
    vpi ans;
    rep(i, 1, T){
        rep(j, 1, i){
            int l = lc.lca(i, j);
            if(l != 0){
                int p1 = rev[j + 1], p2 = rev[i + 1];
                if(p1 > p2) swap(p1, p2);
                ans.pb({p1, p2});
            }
        }
    }
    sort(all(ans));
    int cnt = 0;

    rep(i, 1, k + 1) if(!vacation[i]) cnt++;
    cout << cnt << nL;
    rep(i, 1, k + 1) if(!vacation[i]) cout << i << " ";
    cout << nL;
    cout << sz(ans) << nL;
    for(auto [p1, p2] : ans){
        cout << p1 << " " << p2 << nL;
    }
    
    return 0;
}
