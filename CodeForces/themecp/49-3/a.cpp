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

void solve() {
    int n; cin >> n;
    vector<vector<array<int, 3>>> child(n);
    rep(i, 1, n){
        int p; cin >> p; p--;
        int a, b; cin >> a >> b;
        child[p].push_back({i, a, b});
    }
    vl res(n);
    auto dfs = [&](int u, vl &path, ll asum, auto &&dfs) -> void {
        if(u) res[u] = upper_bound(all(path), asum) - begin(path) - 1;
        for(auto [v, a, b] : child[u]){
            path.push_back(path.back() + b);
            dfs(v, path, asum + a, dfs);
            path.pop_back();
        }
    };
    vl path{0};
    dfs(0, path, 0, dfs);
    rep(i, 1, n) cout << res[i] << " ";
    cout << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn,0, nc){
        solve();
    }
    
    return 0;
}
