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
    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        if(n == 2){
            cout << max(a[0] + a[1], 2 * (max(a[0], a[1]) - min(a[0], a[1]))) << "\n";
            continue;
        }
        ll ans = accumulate(all(a), 0LL);
        rep(i, 0, n){
            if(i != 1 && i != n-2){
                ans = max(ans, a[i] * n);
            }
        }
        if(n == 3) {
            rep(i, 0, 3){
                rep(j, i+1, 3){
                    ll r = abs(a[i] - a[j]);
                    ans = max(ans, r * 3);
                }
            }
            ans = max(ans, abs(a[0] - a[1]) + 2 * abs(abs(a[0] - a[1]) - a[2]));
            ans = max(ans, abs(a[2] - a[1]) + 2 * abs(abs(a[2] - a[1]) - a[0]));
        } else {
            ans = max(ans, max(a[1], a[n-2]) * n);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
