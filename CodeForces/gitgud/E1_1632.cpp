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
        rep(i, 0, n-1){
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vvi d(n, vi(n));
        auto dfs = [&](int u, int p, int s, auto &&dfs) -> void {
            for(int v : adj[u]){
                if(v == p) continue;
                d[s][v] = d[s][u] + 1;
                dfs(v, u, s, dfs);
            }
        };
        rep(i, 0, n){
            dfs(i, -1, i, dfs);
        }
        // add edge 0-a. then find furthest node b from a. res(b) = min(d(b, 0), dist(b, a) + x)
        // for every node, modify it when dist(b, a) + x > d(b, 0) -> x == d(b, 0) - dist(b, a)
        vi ans(n+1, n);
        rep(a, 0, n){
            multiset<int> ms;
            int mxd = 0;
            vvi rem(n);
            rep(i, 0, n){
                if(d[a][i] > d[0][i]){
                    mxd = max(mxd, d[0][i]);
                    continue;
                }
                ms.insert(d[a][i]);
                rem[d[0][i] - d[a][i]].pb(i);
            }
            rep(i, 0, n){
                for(int j : rem[i]){
                    ms.erase(ms.find(d[a][j]));
                    mxd = max(mxd, d[0][j]);
                }
                int curd = mxd;
                if(sz(ms)) curd = max(curd, *(ms.rbegin()) + i);
                ans[i] = min(ans[i], curd);
            }
            ans[n] = min(ans[n], mxd);
        }
        rep(i, 1, n+1){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
