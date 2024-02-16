#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, source, sink; cin >> n >> m >> source >> sink;
    vector<vector<pair<int, ll>>> adj(n);
    rep(i, 0, m){
        int a, b; ll w; cin >> a >> b >> w;
        // a--, b--;
        adj[a].push_back({b, w});
    }
    ll inf = 1e18;
    vector<vector<ll>> dp(n, vector<ll>(2, -1));
    dp[sink] = {0, 0};

    auto solve = [&](int u, int t, auto &&solve) -> ll {
        if(dp[u][t] != -1) return dp[u][t];
        // cout << u << " " << t << endl;
        ll &ans = dp[u][t];
        ans = inf;
        ll bestsofar = t ? inf : 0;
        for(auto [v, w] : adj[u]){
            ll nex = solve(v, 1 - t, solve);
            if(nex != inf){
                nex += w;
            }
            if(t) bestsofar = min(bestsofar, nex);
            else bestsofar = max(bestsofar, nex);
        }
        return ans = bestsofar;
    };
    ll ans = solve(source, 0, solve);
    if(ans == inf){
        cout << "infinity\n";
    }
    else{
        cout << ans << "\n";
    }

    return 0;
}