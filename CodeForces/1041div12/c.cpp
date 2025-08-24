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
        vi a(n), b(n);
        rep(i, 0, n) cin >> a[i];
        rep(i, 0, n) cin >> b[i];
        ll ans = 0;
        rep(i, 0, n) ans += abs(a[i] - b[i]);
        vii events;
        rep(i, 0, n) {
            events.emplace_back(min(a[i], b[i]), max(a[i], b[i]));
        }
        sort(all(events));
        int inc = 1e9+10;
        rep(i, 1, n) {
            if(events[i-1].s >= events[i].f) {
                inc = 0;
                break;
            }
            inc = min(inc, events[i].f - events[i-1].s);
        }
        cout << ans+2*inc << "\n";
    }
    
    return 0;
}
