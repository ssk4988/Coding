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
        rep(i, 0, n) cin >> a[i];
        vl mns;
        ll diff = 1e9;
        ll base = 0;
        ll ans = 0;
        {
            ll mn = 1e9;
            rep(i, 0, n) {
                mn = min(mn, a[i]);
                base += mn;
            }
            ans = base;
        }
        ll cur = 0;
        rep(i, 0, n) {
            if(i) ans = min(ans, cur + min(a[i], diff));
            if(i != sz(mns)) ans = min(ans, cur);
            if(i == 0 || mns.back() > a[i]) {
                mns.pb(a[i]);
                if(sz(mns) >= 2) diff = min(diff, mns[sz(mns)-2]-mns[sz(mns)-1]);
            }
            cur += mns.back();
        }
        cout << ans << "\n";
    }
    
    return 0;
}
