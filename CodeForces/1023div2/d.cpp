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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0, n-1) {
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vi rem(n);
        vi ans;
        using a3 = array<int, 3>;
        set<a3> diams;
        auto recalc = [&](int root) -> void {
            // {best diam, {deepest, id}}
            auto dfs = [&](int u, int p, auto &&dfs) -> pair<a3, pii> {
                pii deepest{1, u};
                a3 best{1, u, u};
                for(int v : adj[u]) {
                    if(v == p || rem[v]) continue;
                    auto [cbest, cdeep] = dfs(v, u, dfs);
                    best = max(best, cbest);
                    best = max(best, a3{deepest.f + cdeep.f, max(deepest.s, cdeep.s), min(deepest.s, cdeep.s)});
                    deepest = max(deepest, pii{cdeep.f+1, cdeep.s});
                }
                return {best, deepest};
            };
            auto [best, deep] = dfs(root, -1, dfs);
            diams.insert(best);
        };
        recalc(0);
        while(sz(diams)) {
            auto [bestdiam, l, r] = *diams.rbegin();
            diams.erase(prev(end(diams)));
            ans.pb(bestdiam);
            ans.pb(l+1);
            ans.pb(r+1);
            auto pathdfs = [&](int u, int p, auto &&self) -> vi {
                if(u == r) return vi{u};
                vi deep;
                for(int v : adj[u]) {
                    if(v == p || rem[v]) continue;
                    vi c = self(v, u, self);
                    if(sz(c) > sz(deep)) swap(c, deep);
                }
                if(sz(deep)) deep.pb(u);
                return deep;
            };
            vi path = pathdfs(l, -1, pathdfs);
            for(int u : path) {
                rem[u] = 1;
            }
            for(int u : path){
                for(int v : adj[u]) {
                    if(!rem[v]) recalc(v);
                }
            }
        }
        for(int v : ans) cout << v << " ";
        cout << "\n";
    }
    
    return 0;
}
