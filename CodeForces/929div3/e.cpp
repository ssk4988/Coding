#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        vl pref(a);
        partial_sum(all(pref), pref.begin());
        pref.insert(pref.begin(), 0);
        int q; cin >> q;
        auto nc2 = [](ll x) -> ll {
            return x * (x + 1) / 2;
        };
        rep(_, 0, q){
            ll l, u; cin >> l >> u; l--;
            ll ans = l+1;
            for(ll dif = 1 << 20; dif; dif >>= 1){
                if(ans + dif <= n && pref[ans + dif] - pref[l] <= u){
                    ans += dif;
                }
            }
            ll cur = pref[ans] - pref[l];
            while(ans < n && nc2(u - cur) - nc2(u - cur - a[ans]) > 0) {
                cur += nc2(u - cur) - nc2(u - cur - a[ans]);
                ans++;
            }
            cout << ans << " ";
        }
        cout << nL;
    }
    
    return 0;
}
