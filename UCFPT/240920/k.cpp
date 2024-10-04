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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0, n-1) {
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        int mnleaf = n;
        rep(i, 0, n){
            if(sz(adj[i]) == 1) mnleaf = min(mnleaf, i);
        }
        vi ord, used(n);
        used[mnleaf] = true;
        ord.pb(mnleaf);
        mnleaf = adj[mnleaf][0];
        vi mns(n, -1);
        auto dfsmn = [&](int u, int p, auto &&dfsmn) -> int {
            if(mns[u] != -1) return mns[u];
            mns[u] = n;
            for(int v : adj[u]) if (v != p) {
                mns[u] = min(mns[u], dfsmn(v, u, dfsmn));
            }
            if(mns[u] == n) mns[u] = u;
            return mns[u];
        };
        auto go = [&](int u, int p, auto &&go) -> void {
            vpi others;
            for(int v : adj[u]) {
                if(!used[v] && v != p) {
                    others.pb({dfsmn(v, u, dfsmn), v});
                }
            }
            sort(all(others));
            reverse(all(others));
            while(sz(others) > 1) {
                auto [m, v] = others.back();
                go(v, u, go);
                others.pop_back();
            }
            if(sz(others) == 1) {
                if(others.back().f > u && p == -1) {
                    used[u] = true;
                    ord.pb(u);
                    return go(others.back().s, -1, go);
                }
                else {
                    go(others.back().s, u, go);
                    others.pop_back();
                } 
            }
            used[u] = true;
            ord.pb(u);
        };
        go(mnleaf, -1, go);
        rep(i, 0, n){
            cout << ord[i]+1 << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
