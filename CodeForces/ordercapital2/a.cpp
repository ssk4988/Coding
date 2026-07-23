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
        // rep(v, 0, 1001) {
            rep(i, 0, n) {
                // if(a[i] != v) continue;
                rep(j, i+1, n) {
                    if(a[j] > a[i]) {
                        a[j] = a[i];
                        break;
                    }
                }
            }
        // }
        int ans = accumulate(all(a), 0);
        cout << ans << "\n";
        // rep(i, 0, n) cout << a[i] << " ";
        // cout << "\n";
    }
    
    
    return 0;
}
