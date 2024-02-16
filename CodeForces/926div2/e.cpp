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
        vector<vpi> adj(n);
        rep(i, 0, n - 1){
            int a, b; cin >> a >> b; a--, b--;
            adj[a].pb({b, i});
            adj[b].pb({a, i});
        }
        vi mask(n-1);
        vi seen;
        int k; cin >> k;
        rep(i, 0, k){
            auto fix = [&](int u, int p, int target, auto &&fix) -> bool {
                if(u == target) return true;
                for(auto [v, id] : adj[u]){
                    if(v == p) continue;
                    if(fix(v, u, target, fix)){
                        mask[id] |= 1 << i;
                        return true;
                    }
                }
                return false;
            };
            int a, b; cin >> a >> b; a--, b--;
            fix(a, -1, b, fix);
        }
        for(int i : mask) if(i) seen.pb(i);
        sort(all(seen));
        seen.erase(unique(all(seen)), seen.end());
        vi ans(1 << k, 1e9);
        ans[0] = 0;
        // cout << "seen: ";
        for(int sub : seen){
            // cout << sub << " ";
            for(int i = sz(ans) - 1; i >= 0; i--) {
                ans[i | sub] = min(ans[i | sub], 1 + ans[i]);
            }
        }
        cout << ans[(1 << k) - 1] << nL;
    }
    
    return 0;
}