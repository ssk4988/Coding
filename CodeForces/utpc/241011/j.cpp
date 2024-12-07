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
    ll n, d; cin >> n >> d;
    vl x(n), y(n);
    rep(i, 0,n){
        cin >> x[i] >> y[i];
    }
    sort(all(x));
    sort(all(y));
    vl starts;
    vl sm;
    int start = n-1;
    int l = 0, r = n-1;
    while(l < r) {
        starts.pb(n-1);
        start -= 2;
        ll cont = 0;
        if(l + 1 == r) {
            cont += x[r] - x[l];
            cont += y[r] - y[l];
        } else {
            cont += x[l+1] - x[l];
            cont += x[r] - x[r-1];
            cont += y[l+1] - y[l];
            cont += y[r] - y[r-1];
        }
        l++, r--;
        sm.pb(cont);
    }
    ll cur = 0;
    ll prvs = 0;
    rep(i, 0, n){
        cur += x[i] * i - prvs;
        prvs += x[i];
    }
    prvs = 0;
    rep(i, 0, n){
        cur += y[i] * i - prvs;
        prvs += y[i];
    }
    // cout << cur << "\n";
    int idx = 0;
    ll ans  = 0;
    ll partial = 0, full = 1;
    rep(i, 0, d) {
        ll t; cin >> t;
        while(idx < sz(sm) && t > 0) {
            if(sm[idx] == 0){
                idx++;
                full = idx+1;
                partial = 0;
                continue;
            }
            if(partial != 0) {
                ll cnt = min(full - partial, t);
                ll val = (full - partial) * (n+1 - 2 * (full - partial) + n+1 - 2 * (full - partial + cnt-1)) / 2;
                cur -= val;
                t -= cnt;
                partial += cnt;
                partial %= full;
                // sm[idx] -= partial == 0;
                continue;
            }
            ll tot = min(sm[idx], t / (1 + idx));
            cur -= tot * (idx + 1) * (n-1 + (n-1 - 2 * idx)) / 2;
            t -= tot * (idx+1);
            sm[idx] -= tot;
            if(tot == 0) {
                cur -= t * (n+1 - 2 * (idx+1) + n+1 - 2 * (idx+1 - (t-1))) / 2;
                full = idx+1;
                (partial += t) %= full;
                sm[idx]--;
                t--;
            }
            // upd partial
        }
        (ans += cur) %= 998244353;
    }
    cout << ans << "\n";
    
    return 0;
}
