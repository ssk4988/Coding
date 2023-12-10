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

vector<vi> treeJump(vi& P){
	int on = 1, d = 1;
	while(on < sz(P)) on *= 2, d++;
	vector<vi> jmp(d, P);
	rep(i,1,d) rep(j,0,sz(P))
		jmp[i][j] = jmp[i-1][jmp[i-1][j]];
	return jmp;
}

int jmp(vector<vi>& tbl, int nod, int steps){
	rep(i,0,sz(tbl))
		if(steps&(1<<i)) nod = tbl[i][nod];
	return nod;
}

int lca(vector<vi>& tbl, vi& depth, int a, int b) {
	if (depth[a] < depth[b]) swap(a, b);
	a = jmp(tbl, a, depth[a] - depth[b]);
	if (a == b) return a;
	for (int i = sz(tbl); i--;) {
		int c = tbl[i][a], d = tbl[i][b];
		if (c != d) a = c, b = d;
	}
	return tbl[0][a];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi depth(n);
    vi p(n);
    
    auto dfs = [&](int cur, int par, int d, auto &&dfs)-> void {
        depth[cur] = d;
        p[cur] = par;
        for(int nex : adj[cur]){
            if(nex == par) continue;
            dfs(nex, cur, d + 1, dfs);
        }
    };
    dfs(0, 0, 0, dfs);
    vvi tbl = treeJump(p);
    int pre = 0;
    vi qs(m);
    int ans = 0;
    bool good = true;
    rep(i, 0, m){
        cin >> qs[i]; qs[i]--;
        if(!good) continue;
        int l = lca(tbl, depth, pre, qs[i]);
        if(l == pre){
            pre = qs[i];
            ans++;
            continue;
        }
        if(l == qs[i]){
            ans++;
            continue;
        }
        int c1 = jmp(tbl, pre, depth[pre] - depth[l] - 1);
        int c2 = jmp(tbl, qs[i], depth[qs[i]] - depth[l] - 1);
        if(c2 < c1){
            good = false;
            continue;
        }
        ans++;
        pre = qs[i];
    }
    cout << ans << nL;
    

    
    return 0;
}
