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

const int B = 2000;
int rem[B];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, m, k; cin >> n >> m >> k;
        // OVERFLOW
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        vi b(m);
        rep(i, 0, m){
            cin >> b[i];
        }
        vi ord;
        rep(i, 0, n) {
            rem[0] = a[i];
            vi best(m+1);
            rep(mask, 1, 1 << m) {
                int pmask = mask - (mask & -mask);
                rem[mask] = rem[pmask] & b[__lg(mask&-mask)];
                int bits = __builtin_popcount(mask);
                best[bits] = max(best[bits], a[i] - rem[mask]);
            }
            for(int j = sz(best)-1; j > 0; j--) {
                best[j] -= best[j-1];
                ord.pb(best[j]);
            }
        }
        sort(all(ord), greater<>());
        ll ans = 0;
        rep(i, 0 ,n) ans += a[i];
        rep(i, 0, min(k, sz(ord))) {
            ans -= ord[i];
        }
        cout << ans << "\n";
    }
    
    return 0;
}
