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
        int n, k, x; cin >> n >> k >> x;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        sort(all(a));
        int ans = INT_MIN;
        // if(k == n) ans = max(ans, 0);
        vi pref(n+1);
        partial_sum(all(a), begin(pref)+1);
        rep(i, 0, n+1) {
            if(i + k >= n) {
                ans = max(ans, pref[max(0, i-x)] * 2 - pref[i]);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
