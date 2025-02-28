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
        ll b, k; cin >> b >> k;
        ll ans = 0;
        ll cur = 0;
        rep(i, 0, min(10LL, k+1)) {
            ans = max(ans, b * (k-i));
            b += b % 10;
            cur++;
        }
        ll inc = (b % 10 > 0 ? 20 : 0);
        rep(t, 0, 4) {
            ll lo = 0, hi = (k-cur)/4;
            while(hi-lo > 5) {
                ll dif = (hi-lo)/3;
                ll m1 = lo+dif, m2 = hi-dif;
                ll a1 = (b + inc * m1) * (k-cur-4*m1);
                ll a2 = (b + inc * m2) * (k-cur-4*m2);
                if(a1 > a2) {
                    hi = m2;
                } else lo = m1;
            }
            rep(m, lo, hi+1) {
                ll a = (b+inc*m) * (k-cur-4*m);
                ans = max(ans, a);
            }
            cur++;
            b += b % 10;
            if(cur > k) break;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
