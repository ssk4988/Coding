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
    int d; cin >> d;
    vvi par(2);
    vvi subsz(2);
    vvi subleaf(2);
    vector<vvi> child(2);
    vi n(2);
    vvi a(2, vi(d));
    vvi depth(2);
    vector<vvi> jmp(2);
    rep(t, 0, 2){
        cin >> n[t];
        par[t].resize(n[t]);
        subsz[t].assign(n[t], 1);
        subleaf[t].resize(n[t]);
        child[t].resize(n[t]);
        depth[t].resize(n[t]);
        rep(i, 1, n[t]){
            int p; cin >> p; p--;
            par[t][i] = p;
            child[t][p].pb(i);
        }
        rep(i, 0, d){
            cin >> a[t][i]; a[t][i]--;
            subleaf[t][a[t][i]]++;
        }
        jmp[t] = treeJump(par[t]);
        auto dfs = [&](int u, auto &&dfs) -> void {
            for(int v : child[t][u]){
                depth[t][v] = 1 + depth[t][u];
                dfs(v, dfs);
                subsz[t][u] += subsz[t][v];
                subleaf[t][u] += subleaf[t][v];
            }
        };
        dfs(0, dfs);
    }
    // CHECK REMOVE ROOT 1, dont count cost
    vi dp(d+1);
    rep(i, 0, d){
        dp[i+1] = max(dp[i+1], dp[i]);
        rep(j, i, d){
            rep(t, 0, 2){
                int l = lca(jmp[t], depth[t], a[t][i], a[t][j]);
                if(subleaf[t][l] > j - i + 1) continue;
                assert(subleaf[t][l] == j - i + 1);
                for(int k = sz(jmp[t]) - 1; k >= 0; k--){
                    if(subleaf[t][jmp[t][k][l]] == j - i + 1){
                        l = jmp[t][k][l];
                    }
                }
                dp[j+1] = max(dp[j+1], dp[i] + subsz[t][l] - (l == 0));
            }
        }
    }
    cout << dp[d] << "\n";
    return 0;
}
