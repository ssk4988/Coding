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
    ll x; int n, m; cin >> x >> n >> m;
    vl xs(n + m);
    vi h(n + m);
    rep(i, 0, n + m) {
        cin >> xs[i];
        char c; cin >> c;
        h[i] = c == 'H';
    }
    vector<set<int>> adj(n + m);
    vi st;
    rep(i, 0, 2 * (n + m)){
        int i1 = i % (n + m);
        if(sz(st) && h[st.back()] != h[i1]) {
            int j1 = st.back(); st.pop_back();
            adj[j1].insert(i1);
            adj[i1].insert(j1);
        } else st.push_back(i1);
    }
    st.clear();
    for(int i = 2 * (n + m) - 1; i >= 0; i--){
        int i1 = i % (n + m);
        if(sz(st) && h[st.back()] != h[i1]) {
            int j1 = st.back(); st.pop_back();
            adj[j1].insert(i1);
            adj[i1].insert(j1);
        } else st.push_back(i1);
    }
    rep(i, 0, n + m){
        // if(h[i]) continue;
        // cout << i << " " << sz(adj[i]) << endl;
        assert(h[i] == 1 || sz(adj[i]) >= 2);
        // assert(h[i] == 0 || sz(adj[i]) <= 2); // true
    }
    vi vis(n + m);
    vl path;
    auto dfs = [&](int u, int p, auto&&dfs) -> void {
        if(vis[u]) return;
        vis[u] = true;
        for(int v : adj[u]){
            if(v == p) continue;
            path.pb(min(abs(xs[u] - xs[v]), x - abs(xs[u] - xs[v])));
            dfs(v, u, dfs);
        }
    };
    ll ans = 1;
    ll cost = 0;
    rep(i, 0, n + m){
        if(sz(adj[i]) == 1 && h[i] && !vis[i]) {
            path.clear();
            dfs(i, -1, dfs);
            // assert(sz(path) % 2 == 0);
            pll best{0, 1};
            for(int j = 1; j < sz(path); j += 2) best.f += path[j];
            ll cur = best.f;
            for(int j = 0; j + 1 < sz(path); j += 2) {
                cur += path[j];
                cur -= path[j + 1];
                if(cur < best.f) best = {cur, 1};
                else if(cur == best.f) best.s++;
            }
            cost += best.f;
            (ans *= best.s) %= 998244353;
        }
    }
    cout << cost << endl << ans << endl;

    
    return 0;
}
