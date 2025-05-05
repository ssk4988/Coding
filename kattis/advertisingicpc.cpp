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
    int n, m; cin >> n >> m;
    vvi grid(n, vi(m, -1));
    string w = "ICP?";
    rep(i, 0, n) {
        string s; cin >> s;
        rep(j, 0, m) {
            grid[i][j] = find(all(w), s[j]) - begin(w);
        }
    }
    vi pw3{1};
    rep(i, 0, 10) pw3.pb(3 * pw3.back());
    auto bitat = [&](int x, int b) { return x / pw3[b] % 3; };
    // row id, col id, profile, made icpc, value we just replaced in previous step
    // ##IC##
    // ##P###
    vector dp(n, vector(m, vector(pw3[m], vector(2, vi(3, -1)))));
    auto go = [&](int row, int col, int profile, int made, int pre, auto &&go) -> int {
        if(row == n) return made;
        int &ans = dp[row][col][profile][made][pre];
        if(ans != -1) return ans;
        ll res = 0;
        rep(nxt, 0, 3) {
            if(grid[row][col] != 3 && grid[row][col] != nxt) continue;
            bool made1 = made;
            if(col >= 1) {
                int topleft = pre, topright = bitat(profile, col), botleft = bitat(profile, col-1), botright = nxt;
                made1 = made1 || (topleft == 0 && topright == 1 && botleft == 2 && botright == 1);
            }
            int profile1 = profile;
            profile1 -= bitat(profile, col) * pw3[col];
            profile1 += nxt * pw3[col];
            int col1 = (col + 1) % m;
            int row1 = row + (col1 == 0);
            res += go(row1, col1, profile1, made1, bitat(profile, col), go);
        }
        return ans = res % 998244353;
    };
    cout << go(0, 0, 0, 0, 0, go) << "\n";
    
    return 0;
}
