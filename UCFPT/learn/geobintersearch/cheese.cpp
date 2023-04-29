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
    int n, s; cin >> n >> s;
    vector<vd> c(n, vd(3));
    vd r(n);
    rep(i, 0, n){
        cin >> r[i];
        r[i] /= 1000;
        rep(j, 0, 3){
            cin >> c[i][j];
            c[i][j] /= 1000;
        }
    }
    ld pi = acos(-1);
    auto cut = [&](int i, ld z)->ld{
        ld c1 = z - c[i][2];
        if(c1 <= -r[i]) return 0;
        if(c1 >= r[i]) return pi * 4 / 3 * r[i] * r[i] * r[i];
        return pi * (r[i] * r[i] * (r[i] + c1) - c1 * c1 * c1 / 3 - r[i] * r[i] * r[i] / 3);
    };
    auto vol = [&](ld z)->ld{
        ld cur = 100 * 100 * z;
        rep(i, 0, n){
            ld c2 = cut(i, z);
            cur -= c2;
        }
        return cur;
    };
    vd ans;
    ld eps = 1e-9;
    ld totvol = vol(100);
    rep(i3, 0, s){
        ld prop = totvol * (i3 + 1) / s;
        ld lo = 0, hi = 100;
        while(fabs(hi - lo) > eps){
            ld mid = (lo + hi) / 2;
            ld v = vol(mid);
            if(v > prop) hi = mid;
            else lo = mid;
        }
        ans.pb(lo);
    }
    for(int i = sz(ans) - 1; i >= 1; i--){
        ans[i] -= ans[i - 1];
    }
    rep(i, 0, sz(ans)){
        cout << fixed << setprecision(8) << ans[i] << nL;
    }
    
    return 0;
}