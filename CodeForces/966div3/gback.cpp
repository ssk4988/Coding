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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vector<vector<array<int, 3>>> adj(n);
        vi t(3);
        rep(i, 0, 3) cin >> t[i];
        rep(i, 0, m){
            int u, v, l1, l2; cin >> u >> v >> l1 >> l2; u--, v--;
            adj[u].pb({v, l1, l2});
            adj[v].pb({u, l1, l2});
        }
        vl d(n, 1e15);
        priority_queue<pll> pq;
        pq.push({t[0], n-1});
        while(!pq.empty()){
            auto [d_u, u] = pq.top(); pq.pop();
            if(d[u] != 1e15) continue;
            d[u] = d_u;
            for(auto [v, l1, l2] : adj[u]){
                pq.push({d_u - (d_u <= t[1] || t[2] <= d_u - l1 ? l1 : l2), v});
                if(d_u > t[1]) pq.push({t[1] - l1, v});
            }
        }
        // rep(i, 0, n){
        //     cout << i << " " << d[i] << "\n";
        // }
        ll ans = max(d[0], -1LL);
        cout << ans << "\n";
    }
    
    return 0;
}
