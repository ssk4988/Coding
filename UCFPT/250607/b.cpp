#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, e, w; cin >> n >> e >> w;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int c; cin >> c;
    vi haswaste(n);
    rep(i, 0, c) {
        int v; cin >> v;
        v--; 
        haswaste[v] = 1;
    }
    int conte = -1, contedepth = 0;
    vi eastdepth, westdepth;
    auto dfs = [&](int u, int p, int d, auto &&dfs) -> int {
        int sub = haswaste[u];
        if(haswaste[u]) {
            eastdepth.push_back(d);
            // cerr << "an eastdepth " << u << " " << d << endl;
        }
        for(int v : adj[u]) if(v != p) {
            sub += dfs(v, u, d+1, dfs);
        }
        if(conte == -1 && sub == c) conte = u, contedepth = d;
        return sub;
    };
    dfs(n-1, -1, 0, dfs);
    int contw = -1, contwdepth = 0;
    auto dfs1 = [&](int u, int p, int d, auto &&dfs1) -> int {
        int sub = u >= n-w;
        if(u >= n-w) {
            westdepth.push_back(d);
        }
        for(int v : adj[u]) if(v != p) {
            sub += dfs1(v, u, d+1, dfs1);
        }
        if(contw == -1 && sub == w) contw = u, contwdepth = d;
        return sub;
    };
    dfs1(0, -1, 0, dfs1);
    auto calcd = [&](int u, int p, auto &&calcd) -> int {
        if(u == conte) return 0;
        int ans = -1e9;
        for(int v : adj[u]) if(v != p) {
            ans = max(ans, 1+calcd(v, u, calcd));
        }
        return ans;
    };
    int span = calcd(contw, -1, calcd);
    sort(all(westdepth));
    westdepth.resize(c);
    int ans = 0;
    sort(all(eastdepth));
    reverse(all(westdepth));
    rep(i, 0, c) {
        if(i) eastdepth[i] = max(eastdepth[i], 1+eastdepth[i-1]);
        // cerr << i << " " << eastdepth[i] << " " << westdepth[i] << endl;
        ans = max(ans, eastdepth[i]-contedepth + westdepth[i]-contwdepth + span);
    }
    // cerr << "conte" << conte << " depth " << contedepth << endl;
    // cerr << "contw" << contw << " depth " << contwdepth << endl;
    // cerr << "span: " << span << endl;
    cout << ans << "\n";
    return 0;
}
