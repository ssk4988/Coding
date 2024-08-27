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
        auto test = [&](int time) -> bool {
            vl d(n, 1e15);
            priority_queue<pll, vll, greater<pll>> pq;
            pq.push({time, 0});
            while(!pq.empty()){
                auto [d_u, u] = pq.top(); pq.pop();
                if(d[u] < d_u) continue;
                d[u] = d_u;
                for(auto [v, l1, l2] : adj[u]){
                    pq.push({d_u + (d_u + l1 <= t[1] || t[2] <= d_u ? l1 : l2), v});
                    if(d_u < t[2]) pq.push({t[2] + l1, v});
                }
            }
            // cout << time << " " << d[n-1] << " " << t[0] << endl;
            return d[n-1] <= t[0];
        };
        int ans = -1;
        for(int dif = 1 << 29; dif; dif /= 2){
            if(test(ans + dif)) ans += dif;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
