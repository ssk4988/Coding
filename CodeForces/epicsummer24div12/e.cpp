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
    rep(cn, 0, nc) {
        int n; cin >> n;
        vl a(n);
        vvi child(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        rep(i, 1, n){
            int p; cin >> p; p--;
            child[p].pb(i);
        }
        vl c(n);
        vector<vpl> ev(n);
        const ll oo = 1e15;
        auto dfs = [&](int u, auto &&dfs) -> void {
            if(sz(child[u]) == 0){
                ev[u].pb({1, oo});
                return;
            }
            int heavyc = -1;
            ll asum = 0;
            for(int v : child[u]){
                dfs(v, dfs);
                c[u] += c[v];
                asum += a[v];
                if(heavyc == -1 || sz(ev[v]) > sz(ev[heavyc])) heavyc = v;
            }
            // cout << u << " " << heavyc << " " << sz(ev[heavyc]) << " " << asum << " " << a[u] << " " << c[u] << endl;
            ll adv = 0;
            if(asum > a[u]){
                ev[u].pb({0, asum - a[u]});
            } else{
                adv = a[u] - asum;
                // a[u] = asum;
            }
            swap(ev[u], ev[heavyc]);
            for(int v : child[u]){
                for(auto p : ev[v]){ ev[u].pb(p); }
                // copy(all(ev[v]), ev[u].end());
            }
            sort(all(ev[u]));
            vpl res;
            for(auto [slope, dist] : ev[u]){
                if(sz(res) && res.back().f == 1 + slope){
                    res.back().s = min(oo, res.back().s + dist);
                } else {
                    res.pb({slope + 1, dist});
                }
            }
            ev[u].clear();
            for(auto [slope, dist] : res){
                if(adv) {
                    ll amt = min(adv, dist);
                    dist -= amt;
                    adv -= amt;
                    c[u] += (slope-1) * amt;
                }
                if(dist) {
                    ev[u].pb({slope, dist});
                }
            }
            // cout << "c at " << u << "is now " << c[u] << endl;
        };
        dfs(0, dfs);
        cout << c[0] << "\n";
    }
    
    return 0;
}
