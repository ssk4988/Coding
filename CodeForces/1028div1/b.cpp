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
        int n, q; cin >> n >> q;
        vi b(n);
        rep(i, 0, n) {
            cin >> b[i];
        }
        vi cur(n);
        iota(all(cur), 0);
        int g = n;
        vvi adj(g);
        vector<array<int, 3>> qs(q);
        rep(i, 0, q) {
            rep(j, 0, 3) {
                cin >> qs[i][j]; qs[i][j]--;
            }
            int a = cur[qs[i][0]], b = cur[qs[i][1]];
            int c1 = cur[qs[i][2]];
            cur[qs[i][2]] = g++;
            adj.pb({});
            int c2 = cur[qs[i][2]];
            adj[a].pb(c2);
            adj[b].pb(c2);
        }
        rep(i, 0, n) {
            int j = cur[i];
            cur[i] = g++;
            adj.pb({});
            adj[j].pb(cur[i]);
        }
        vi dp(g, -1);
        rep(i, 0, n) {
            dp[i+g-n] = b[i];
        }
        auto go = [&](int u, auto &&go) -> int {
            int &ans = dp[u];
            if(ans != -1) return ans;
            ans = 0;
            for(int v : adj[u]) {
                ans = max(ans, go(v, go));
            }
            return ans;
        };
        rep(i, 0, g) go(i, go);
        vi a(n);
        rep(i, 0, n) a[i] = dp[i];
        rep(i, 0, q) {
            auto [x, y, z] = qs[i];
            a[z] = min(a[x], a[y]);
        }
        if(a != b) {
            cout << "-1\n";
            continue;
        }
        rep(i, 0, n) {
            cout << dp[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
