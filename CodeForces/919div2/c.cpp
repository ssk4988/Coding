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
        int ans = 0;
        rep(d, 1, n+1) {
            if(n % d != 0) continue;
            int g = 0;
            rep(i, 0, d) {
                for(int j = i, prv = a[i]; j < n; prv = a[i], j += d) {
                    g = gcd(g, abs(a[j] - prv));
                }
            }
            if(g == 0 || g > 1) 
                ans++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
