#include <bits/stdc++.h>
using namespace std;
#define int long long

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n, k; cin >> n >> k;
    int q; cin >> q;

    vvi arr(n, vi(n));
    vvi sums(n-k+1, vi(n-k+1));

    int mx = 0;
    while(q--) {
        int r, c, v; cin >> r >> c >> v; r--, c--;
        rep(si, max(0ll, r-k+1), min(r+1, n-k+1))
            rep(sj, max(0ll, c-k+1), min(c+1, n-k+1)) {
                sums[si][sj] += v - arr[r][c]; 
                mx = max(mx, sums[si][sj]);
            }
        arr[r][c] = v;
        cout << mx << '\n';
    }

    return 0;
}
