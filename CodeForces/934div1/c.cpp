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
            int a, b; cin >> a >> b; a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        auto furthest = [&](int u, int p, auto &&furthest) -> vi {
            vi best;
            for(int v : adj[u]){
                if(v == p) continue;
                vi cur = furthest(v, u, furthest);
                if(sz(cur) > sz(best)) swap(cur, best);
            }
            best.pb(u);
            return best;
        };
        vi diam = furthest(0, -1, furthest);
        diam = furthest(diam[0], -1, furthest);
        vpi ans;
        if(sz(diam) % 4 == 0){
            int c1 = diam[sz(diam) / 2], c2 = diam[sz(diam) / 2 - 1];
            rep(i, 0, sz(diam) / 4){
                ans.pb({c1, i * 2 + 1});
                ans.pb({c2, i * 2 + 1});
            }
        }
        else {
            int c = diam[sz(diam) / 2];
            int times = sz(diam) / 2 + 1;
            rep(i, 0, times){
                ans.pb({c, i});
            }
        }
        cout << sz(ans) << "\n";
        for(auto [v, d] : ans){
            cout << (v + 1) << " " << d << "\n";
        }
    }
    
    return 0;
}
