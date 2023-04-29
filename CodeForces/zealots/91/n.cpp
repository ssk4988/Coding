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

int n, l;
vector<vector<int>> adj;
vector<vpi> wadj;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;
vector<vector<int>> mxup;

void dfs(int v, int p, int w)
{
    tin[v] = ++timer;
    up[v][0] = p;
    mxup[v][0] = w;
    for (int i = 1; i <= l; ++i){
        up[v][i] = up[up[v][i-1]][i-1];
        mxup[v][i] = max(mxup[v][i - 1], mxup[up[v][i - 1]][i - 1]);
    }
    for (pi &u : wadj[v]) {
        if (u.f != p)
            dfs(u.f, v, u.s);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

int maxtolca(int u, int v){
    int lc = lca(u, v);
    int max1 = 0;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], lc)){
            max1 = max(max1, mxup[u][i]);
            u = up[u][i];
        }
    }
    if(lc != u)
        max1 = max(max1, mxup[u][0]);
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[v][i], lc)){
            max1 = max(max1, mxup[v][i]);
            v = up[v][i];
        }
    }
    if(lc != v)
        max1 = max(max1, mxup[v][0]);
    return max1;
}

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    mxup.assign(n, vector<int>(l + 1));
    dfs(root, root, 0);
}

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int m; cin >> n >> m;
    adj.resize(n);
    wadj.resize(n);
    vvi edges;
    rep(i, 0, m){
        int a, b, w; cin >> a >> b >> w;
        a--,b--;
        // wadj[a].pb({b, w});
        // wadj[b].pb({a, w});
        edges.pb({w, a, b, i});
    }
    // if(m == 0) return 0;
    sort(all(edges));
    vvi mst;
    UF uf(n);
    ll mstsum = 0;
    set<vi> mstset;
    rep(i, 0, m){
        if(!uf.sameSet(edges[i][1], edges[i][2])){
            mst.pb(edges[i]);
            mstset.insert(edges[i]);
            uf.join(edges[i][1], edges[i][2]);
            mstsum += edges[i][0];
        }
    }
    rep(i, 0, sz(mst)){
        adj[mst[i][1]].pb(mst[i][2]);
        adj[mst[i][2]].pb(mst[i][1]);
        wadj[mst[i][1]].pb({mst[i][2], mst[i][0]});
        wadj[mst[i][2]].pb({mst[i][1], mst[i][0]});
    }
    preprocess(0);
    vi ans(m);
    rep(i, 0, m){
        if(mstset.count(edges[i])){
            ans[edges[i][3]] = edges[i][0] - edges[i][0];
        }
        else{
            ans[edges[i][3]] = edges[i][0] - maxtolca(edges[i][1], edges[i][2]);
        }
    }
    rep(i, 0, m){
        cout << (mstsum + ans[i]) << nL;
    }
    
    return 0;
}