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
        vvi a(n, vi(4));
        ll ans = 0;
        rep(i, 0, n) {
            rep(j, 0, 4) cin >> a[i][j];
            ans += abs(a[i][0] - a[i][2]) +  abs(a[i][1] - a[i][3]);
        }
        ans /= 2;
        rep(i, 0, n) {
            if(a[i][3] < a[i][1]) {
                ans += min(a[i][0], a[i][2]);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
