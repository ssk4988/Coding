#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = float;
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

vector<vi> treeJump(vi &P)
{
    int on = 1, d = 1;
    while (on < sz(P))
        on *= 2, d++;
    vector<vi> jmp(d, P);
    rep(i, 1, d) rep(j, 0, sz(P))
        jmp[i][j] = jmp[i - 1][jmp[i - 1][j]];
    return jmp;
}
int jmp(vector<vi> &tbl, int nod, int steps)
{
    rep(i, 0, sz(tbl)) if (steps & (1 << i)) nod = tbl[i][nod];
    return nod;
}
int lca(vector<vi> &tbl, vi &depth, int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);
    a = jmp(tbl, a, depth[a] - depth[b]);
    if (a == b)
        return a;
    for (int i = sz(tbl); i--;)
    {
        int c = tbl[i][a], d = tbl[i][b];
        if (c != d)
            a = c, b = d;
    }
    return tbl[0][a];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n, k, m;
        cin >> n >> k >> m;
        vector<vpi> adj(n);
        rep(i, 0, n - 1)
        {
            int a, b, w;
            cin >> a >> b >> w;
            a--, b--;
            adj[a].pb({b, w});
            adj[b].pb({a, w});
        }
        vi p(n), d(n);
        vl ws(n);
        auto dfs = [&](int cur, int par, int dep, auto &&dfs) -> void
        {
            p[cur] = par;
            d[cur] = dep;
            for (auto [nex, w] : adj[cur])
            {
                if (nex == par)
                    continue;
                ws[nex] = w;
                dfs(nex, cur, dep + 1, dfs);
            }
        };
        dfs(0, 0, 0, dfs);
        vvi jmp = treeJump(p);
        vi net(n);
        rep(i, 0, m){
            int u, v; cin >> u >> v; u--, v--;
            int lc = lca(jmp, d, u, v);
            net[u]++;
            net[v]++;
            net[lc] -= 2;
        }
        if(n == 1){
            cout << 0 << nL;
            continue;
        }
        auto dfs1 = [&](int cur, int par, auto &&dfs1)->int{
            int up = net[cur];
            for(auto [nex, w] : adj[cur]){
                if(nex == par) continue;
                up += dfs1(nex, cur, dfs1);
            }
            ws[cur] *= up;
            return up;
        };
        dfs1(0, 0, dfs1);
        if(k == 1){
            ll ans = 0;
            rep(i, 0, n) ans += ws[i];
            cout << ans << nL;
            continue;
        }
        // rep(i, 0, n){
        //     cout << i << " " << ws[i] << nL;
        // }
        ll ans = 0;
        // max saved at node i by using j vertices, assuming lca is above i
        vector<vl> dp(n, vl(k + 1));
        auto calc = [&](int cur, int par, auto &&calc)->void{
            vl difs, difl, diff;
            // difs.pb(0); // add me
            diff.pb(0); // use one on myself
            int numchild = 0;
            for(auto [nex, w] : adj[cur]){
                if(nex == par) continue;
                calc(nex, cur, calc);
                // numchild++;
                // difs.pb(ws[nex]);
                difs.pb(ws[nex] + dp[nex][1] - dp[nex][0]);
                diff.pb(ws[nex] + dp[nex][1] - dp[nex][0]);
                // cout << "from " << nex << " to " << cur << ": " << diff.back() << nL;
                rep(i, 1, k){
                    difs.pb(dp[nex][i + 1] - dp[nex][i]);
                    difl.pb(dp[nex][i + 1] - dp[nex][i]);
                    // if(difs.back() == 0){
                    //     difs.pop_back();
                    //     break;
                    // }
                }
            }
            if(sz(difs) == 0) return;
            ll aslca = 0;
            sort(all(diff));
            reverse(all(diff));
            rep(i, 0, 2){
                aslca += diff[i];
            }
            rep(i, 2, sz(diff)){
                difl.pb(diff[i]);
            }
            sort(all(difl));
            reverse(all(difl));
            // difl.resize(k - 2);
            rep(i, 0, k - 2){
                aslca += difl[i];
            }
            // cout << "with " << cur << " as lca: " << aslca << nL;
            ans = min(ans, -aslca);
            sort(all(difs));
            reverse(all(difs));
            difs.resize(k);
            rep(i, 0, k){
                dp[cur][i + 1] = dp[cur][i + 1 - 1] + difs[i];
            }
        };
        calc(0, 0, calc);
        
        // tries to consider choosing one node at top to connect to others, doesnt consider if two in different subtrees
        // rep(j, 0, n){
        //     rep(i, 0, k + 1){
        //         ans = min(ans, -dp[0][i]);
        //     }
        // }
        rep(i, 0, n) ans += ws[i];
        cout << ans << nL;
        // rep(i, 0, n){
        //     rep(j, 0, k + 1){
        //         cout << i << " " << j << " " << dp[i][j] << nL;
        //     }
        // }
    }

    return 0;
}
