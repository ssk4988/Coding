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
        int n, q; cin >> n >> q;
        vi par(n);
        par[0] = -1;
        vvi child(n);
        rep(i, 1, n){
            cin >> par[i]; par[i]--;
            child[par[i]].pb(i);
        }
        vi perm(n), inv(n);
        rep(i, 0 ,n){
            cin >> perm[i]; perm[i]--;
            inv[perm[i]] = i;
        }
        vi depth(n), subsz(n, 1);
        auto dfs = [&](int u, auto &&dfs) ->void {
            for(int v : child[u]){
                depth[v] = 1 + depth[u];
                dfs(v, dfs);
                subsz[u] += subsz[v];
            }
        };
        // auto cmp = [&](int a, int b) -> bool {
        //     return depth[a] > depth[b];
        // };
        dfs(0, dfs);
        vi good(n);
        int goodcnt = 0;
        auto calc = [&](int u, auto &&calc) -> void {
            goodcnt -= good[u];
            good[u] = 1;
            for(int v : child[u]){
                good[u] = good[u] && good[v];
            }
            if(inv[u] + subsz[u] > n){
                good[u] = 0;
            } else {
                for(int place = inv[u] + 1; place < inv[u] + subsz[u];) {
                    if(find(all(child[u]), perm[place]) != child[u].end()){
                        place += subsz[perm[place]];
                    } else {
                        good[u] = 0;
                        break;
                    }
                }
            }
            goodcnt += good[u];
            if(par[u] != -1) calc(par[u], calc);
        };
        rep(i, 0, n){
            calc(i, calc);
        }
        rep(i, 0, q){
            int x, y; cin >> x >> y; x--, y--;
            swap(perm[x], perm[y]);
            swap(inv[perm[x]], inv[perm[y]]);
            calc(perm[x], calc);
            calc(perm[y], calc);
            cout << (goodcnt == n ? "YES" : "NO") << "\n";
        }
    }
    
    return 0;
}
