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
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        if(a[0] != a[n-1]) {
            cout << "0\n";
            continue;
        }
        int prv = -1;
        int ans = n;
        rep(i, 0, n) {
            if(a[i] != a[0]) {
                ans = min(ans, i-1-prv);
                prv = i;
            }
        }
        ans = min(ans, n-1-prv);
        if(ans >= n) ans = -1;
        cout << ans << "\n";

    }
    
    return 0;
}
