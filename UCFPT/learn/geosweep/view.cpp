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
    int n; cin >> n;
    ll w; cin >> w;
    vl x(n);
    vd y(n);
    rep(i, 0, n){
        cin >> x[i] >> y[i];
    }
    cout << fixed << setprecision(9);
    if(x.back() - x[0] <= w) {
        ld sum = 0;
        rep(i, 0, n-1){
            sum += (y[i+1] + y[i]) / 2 * (x[i+1] - x[i]);
        }
        sum /= w;
        cout << sum << "\n";
        return 0;
    }
    ld ans = 0;
    ld cur = 0;
    int l = 0, r = 0;
    ll xl = x[l], xr = x[r];
    while(r+1 < n && xr - xl < w){
        if(x[r+1] - xl <= w) {
            cur += (y[r+1] + y[r]) / 2 * (x[r+1] - x[r]);
            r++;
            xr = x[r];
        } else {
            ld slope = (y[r+1] - y[r]) / (x[r+1] - x[r]);
            ll dx = w - (xr - xl);
            xr += dx;
            cur += (y[r] + y[r] + slope * dx) / 2 * dx;
        }
        ans = max(ans, cur);
    }
    // cout << ans << " " << xl << " " << xr << " " << l << " " << r << "\n";
    while(xr != x.back()){
        while(l + 1 < n && x[l+1] <= xl) l++;
        while(r + 1 < n && x[r+1] <= xr) r++;
        ll adv = min(x[r+1] - xr, x[l + 1] - xl);
        ld slopel = (y[l+1] - y[l]) / (x[l+1] - x[l]);
        ld sloper = (y[r+1] - y[r]) / (x[r+1] - x[r]);
        ld curl = y[l] + slopel * (xl - x[l]);
        ld curr = y[r] + sloper * (xr - x[r]);
        if(curr > curl && sloper < slopel && curl + slopel * adv > curr + sloper * adv) {
            ld toadv = (curl - curr) / (sloper - slopel);
            ans = max(ans, cur - (curl + curl + slopel * toadv) / 2 * toadv + (curr + curr + sloper * toadv) / 2 * toadv);
        }
        cur -= (curl + curl + slopel * adv) / 2 * adv;
        cur += (curr + curr + sloper * adv) / 2 * adv;
        xr += adv;
        xl += adv;
        ans = max(ans, cur);
    }
    ans /= w;
    cout << ans << "\n";
    
    return 0;
}
