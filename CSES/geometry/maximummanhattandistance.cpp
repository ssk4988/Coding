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
    vll pts(n);
    ll ans = 0;
    vl best(4, 4e9);
    rep(i, 0, n) {
        cin >> pts[i].f >> pts[i].s;
        rep(mask, 0, 4) {
            ll cur = pts[i].f * ((mask & 1) ? 1 : -1) + pts[i].s * ((mask & 2) ? 1 : -1);
            ans = max(ans, cur - best[mask]);
        }
        rep(mask, 0, 4) {
            ll cur = pts[i].f * ((mask & 1) ? 1 : -1) + pts[i].s * ((mask & 2) ? 1 : -1);
            best[mask] = min(best[mask], cur);
        }
        cout << ans << "\n";
    }

    
    return 0;
}
