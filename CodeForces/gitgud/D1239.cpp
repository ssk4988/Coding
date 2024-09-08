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
        int n, m; cin >> n >> m;
        vvi adj(n), radj(n);
        rep(i, 0, m){
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            radj[v].pb(u);
        }
        vi fnd0(n), fnd1(n);

        auto dfs = [&](vvi &g, vi &fnd, int u, auto &&dfs) -> void {
            if(fnd[u]) return;
            fnd[u] = 1;
            for(int v : g[u]){
                dfs(g, fnd, v, dfs);
            }
        };
        dfs(adj, fnd0, 0, dfs);
        dfs(radj, fnd1, 0, dfs);
        int cnt0 = accumulate(all(fnd0), 0);
        int cnt1 = accumulate(all(fnd1), 0);
        if(cnt0 == n && cnt1 == n){
            cout << "No\n";
            continue;
        }
        cout << "Yes\n";
        bool sw = cnt0 == n;
        vi fnd = sw ? fnd1 : fnd0;
        int cnt = sw ? cnt1 : cnt0;
        int on = sw ? n - cnt : cnt;
        cout << on << " " << n-on << "\n";
        rep(i, 0, n){
            if(sw != fnd[i]) cout << i+1 << " ";
        }
        cout << "\n";
        rep(i, 0, n){
            if(sw == fnd[i]) cout << i+1 << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
