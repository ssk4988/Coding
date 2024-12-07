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
    int n, m, a, b; cin >> n >> m >> a >> b;
    vector<vector<pair<int, ll>>> radjc(n), radje(n);
    rep(i, 0, m){
        int u, v, c, e; cin >> u >> v >> c >> e;
        u--, v--;
        radjc[v].pb({u, c});
        radje[v].pb({u, e});
    }
    vi s(a), t(b);
    rep(i, 0, a) {
        cin >> s[i]; s[i]--;
    }
    rep(i, 0, b){
        cin >> t[i]; t[i]--;
    }
    const ll inf = 1e18;
    auto dijk = [&](auto &adj) -> vl {
        priority_queue<pll, vll, greater<>> pq;
        vl dist(n, inf);
        for(int u : t){
            pq.push({0LL, ll(u)});
        }
        while(sz(pq)){
            auto [d_u, u] = pq.top(); pq.pop();
            if(dist[u] != inf) continue;
            dist[u] = d_u;
            for(auto [v, w] : adj[u]) {
                pq.push(pll{d_u + w, ll(v)});
            }
        }
        return dist;
    };
    vl fromc = dijk(radjc), frome = dijk(radje);
    vl tc, te;
    for(int u : s) {
        if(fromc[u] != inf){
            tc.pb(fromc[u]);
        }
        if(frome[u] != inf) te.pb(frome[u]);
    }
    ll winc = 0, wine = 0;
    sort(all(tc));
    sort(all(te));
    int p = 0;
    rep(i, 0, sz(tc)) {
        winc += a - sz(te);
        while(p < sz(te) && te[p] <= tc[i]) p++;
        winc += sz(te) - p;
    }
    p = 0;
    rep(i, 0, sz(te)){
        wine += a - sz(tc);
        while(p < sz(tc) && tc[p] <= te[i]) p++;
        wine += sz(tc) - p;
    } 


    if(winc == wine) cout << "tie\n";
    else if(winc > wine){
        cout << "chicken\n";
    }
    else cout << "egg\n";
    return 0;
}
