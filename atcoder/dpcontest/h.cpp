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
    int n; cin >> n;
    vector<string> grid(n);
    rep(i, 0, n) cin >> grid[i];
    vvi mn(n, vi(n, 1e9)), mx(n, vi(n, -1));
    mn[0][0] = mx[0][0] = 0;
    vi pref(2*n+5);
    rep(i, 0, n) {
        rep(j, 0, n) {
            if(i+1 < n) {
                mn[i+1][j] = min(mn[i+1][j], mn[i][j] + (grid[i+1][j] == '@'));
                mx[i+1][j] = max(mx[i+1][j], mx[i][j] + (grid[i+1][j] == '@'));
            }
            if(j+1 < n) {
                mn[i][j+1] = min(mn[i][j+1], mn[i][j] + (grid[i][j+1] == '@'));
                mx[i][j+1] = max(mx[i][j+1], mx[i][j] + (grid[i][j+1] == '@'));
            }
            pref[mn[i][j]]++;
            pref[mx[i][j]+1]--;
        }
    }
    rep(i, 0, 2*n-1) {
        if(i) pref[i] += pref[i-1];
        cout << pref[i] << "\n";
    }
    return 0;
}
