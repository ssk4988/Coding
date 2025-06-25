#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m; cin >> n >> m;
    vector<vector<char>> grid(n);
    rep(i, 0, n) {
        string s; cin >> s;
        rep(j, 0, m) grid[i].push_back(s[j]);
    }
    ll ans = 0;
    rep(t, 0, 4) {
        vvi cur(n, vi(m, 1));
        rep(i, 1, n) {
            rep(j, 1, m) {
                if(grid[i][j] == grid[i-1][j] && grid[i][j] == grid[i][j-1]) cur[i][j] += min(cur[i-1][j], cur[i][j-1]);
                ans += cur[i][j]-1;
            }
        }
        vector<vector<char>> grid2(m, vector<char>(n));
        rep(i, 0, n) {
            rep(j, 0, m) {
                grid2[j][n-1 - i] = grid[i][j];
            }
        }
        swap(n, m);
        grid = grid2;
    }
    cout << ans << "\n";

    return 0;
}
