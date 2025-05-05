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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; ll k; cin >> n >> k;
        ll cur = 0;
        rep(i, 0, n) {
            cur += ll(i) * (n-1-i);
        }
        cerr << cur << endl;
        if(cur + 1 < k) {
            cout << "No\n";
            continue;
        }
        int maxdepthanchor = 0;
        vii edges;
        for(int depth = n-1; depth > 0; depth--) {
            if(depth <= maxdepthanchor) {
                edges.pb({depth, depth-1});
                continue;
            }
            int up = 0;
            for(int dif = 1 << 20; dif; dif /= 2) {
                ll test = up + dif;
                if(depth-1 - test < maxdepthanchor) continue;
                ll sub = test * (test+1) / 2;
                if(cur - sub >= k-1) {
                    up = test;
                }
            }
            ll sub = ll(up) * ll(up+1) / 2;
            cur -= sub;
            maxdepthanchor = max(maxdepthanchor, depth-1 - up);
            edges.pb({depth, depth-1-up});
        }
        ll test = 0;
        vvi adj(n);
        for(auto [u, v] : edges) {
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vl subsz(n, 1);
        auto dfs = [&](int u, int p, ll d, auto &&dfs) -> void {
            for(int v : adj[u]) if(v != p) {
                dfs(v, u, d+1, dfs);
                test += d * subsz[u] * subsz[v];
                subsz[u] += subsz[v];
            }
        };
        dfs(0, -1, 0, dfs);
        if(abs(cur-k) > 1) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            for(auto [u, v] : edges){
                cout << u+1 << " " << v+1 << "\n";
            }
        }
        // cerr << "attempt: " << cur << " " << test << endl;
        assert(cur == test);
    }
    
    return 0;
}
