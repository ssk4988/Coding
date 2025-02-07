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
        vl a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }
        ll ans = accumulate(all(a), 0LL);
        vl a2(a);
        rep(t, 0, 2) {

            rep(i, 1, n) {
                vl b;
                rep(j, 1, sz(a)){
                    b.push_back(a[j] - a[j-1]);
                }
                ll s = accumulate(all(b), 0LL);
                ans = max(ans, s);
                ans = max(ans, -s);
                a = b;
            }
            assert(sz(a) == 1);
            reverse(all(a2));
            a = a2;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
