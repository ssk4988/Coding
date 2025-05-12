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
        int n, d; cin >> n >> d;
        vvi child(n);
        rep(i, 1, n) {
            int p; cin >> p; p--;
            child[p].pb(i);
        }
        vi dest(n);
        rep(i, 0, d) {
            int u; cin >> u; u--;
            dest[u] = 1;
        }
        int ans = 0;
        auto dfs = [&](int u, int d, auto &&dfs) -> void {
            for(int v : child[u]) {
                dfs(v, d+1, dfs);
                if(dest[v]) ans++;
                dest[u] += dest[v];
            }
        };
        dfs(0, 0, dfs);
        cout << ans << "\n";
    }
    
    return 0;
}
