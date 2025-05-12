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
    vi a(n), b(m);
    rep(i, 0, n) cin >> a[i];
    rep(i, 0, m) cin >> b[i];
    vvi dp(n+1, vi(m+1, -1));
    auto go = [&](int i, int j, auto &&go) -> int {
        if(i == n || j == m) return 0;
        int &ans = dp[i][j];
        if(ans != -1) return ans;
        ans = max(go(i+1, j, go), go(i, j+1, go));
        if(a[i] == b[j]) ans = max(ans, 1+go(i+1, j+1, go));
        return ans;
    };
    int ans = go(0, 0, go);
    int i = 0, j = 0;
    cout << ans << "\n";
    while(ans) {
        if(go(i+1, j, go) == ans) {
            i++;
            continue;
        }
        if(go(i, j+1, go) == ans) {
            j++;
            continue;
        }
        if(a[i] == b[j] && 1+go(i+1, j+1, go) == ans) {
            cout << a[i] << " ";
            ans--;
            i++, j++;
            continue;
        }
        assert(false);
    }
    cout << "\n";

    return 0;
}
