#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

const int MAXK = 1e6+1;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q; cin >> n >> q;

    vi k(q);
    rep(i, 0, q) cin >> k[i];

    vvi adj(n);
    rep(i, 1, n) {
        int p; cin >> p; p--;
        adj[p].push_back(i);
    }

    vi depth(n);
    auto dfs = [&](int cur, auto &dfs) -> void {
        for(int nxt: adj[cur]) {
            depth[nxt] = depth[cur] + 1;
            dfs(nxt, dfs);
        }
    };
    dfs(0, dfs);

    int max_depth = *max_element(all(depth));

    vi cnt(max_depth+1);
    rep(i, 0, n)
        cnt[depth[i]]++;
    
    vi split(MAXK, max_depth+1);
    // for this k, whats the first depth where width of level > k
    rep(i, 0, max_depth+1)
        split[cnt[i]-1] = min(split[cnt[i]-1], i);
    
    for(int i = MAXK-2; i >= 0; i--)
        split[i] = min(split[i], split[i+1]);
    
    for(int i = sz(cnt)-2; i >= 0; i--)
        cnt[i] += cnt[i+1];

    for(int ki: k)
        cout << split[ki] + ((cnt[split[ki]] + ki - 1) / ki) << ' ';
    cout << '\n';

    return 0;
}
