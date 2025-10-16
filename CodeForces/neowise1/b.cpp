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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        vl l(n), r(n);
        rep(i, 0, n) cin >> l[i];
        rep(i, 0, n) cin >> r[i];
        vi ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int a, int b) { return min(l[a], r[a]) > min(l[b], r[b]); });
        ll ans = 1;
        rep(i, 0, k-1) ans += min(l[ord[i]], r[ord[i]]);
        rep(i, 0, n) ans += max(l[ord[i]], r[ord[i]]);
        cout << ans << "\n";
    }
    
    return 0;
}
