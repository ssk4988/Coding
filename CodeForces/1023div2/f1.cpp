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
const int N = 5002;
ll memo[N][N];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vl a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }
        rep(i, 0, n) {
            rep(j, 0, n+1) memo[i][j] = -1;
        }
        const ll inf = 1e18;
        auto go = [&](int at, int have, auto &&go) -> ll {
            if(at == -1) return 0;
            // memo
            ll &ans = memo[at][have];
            if(ans != -1) return ans;
            ans = inf;
            if(have == n) {
                rep(bring, 0, at) {
                    ans = min(ans, go(at, bring, go) + at-bring);
                }
                return ans;
            }
            if(at-1 < have) ans = min(ans, go(at-1, at-1, go) + a[have]);
            ans = min(ans, go(at-1, have, go) + a[have]+1);
            if(have >= at) {
                // get another guy
                ans = min(ans, go(at, n, go));
            }
            // cerr << at << "," << have << " " << ans << endl;
            return ans;
        };
        ll ans = go(n-1, n-1, go);
        cout << ans << "\n";
    }
    
    return 0;
}
