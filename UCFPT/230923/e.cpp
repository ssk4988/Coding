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
    ld d, s, r, o; cin >> d >> s >> r >> o;
    ld d1 = d * acosl(-1) / 2;
    // ld theta = asinl(d1 / s);
    ld a = sinl(d1 / s);
    // cout << a << nL;
    ld ans = (o / 2 - r) / a + s - r;
    cout << fixed << setprecision(1);
    if(ans < 1e-6){
        cout << -1.0 << nL;
        return 0;
    }
    if(s - 2 * r - ans < 1e-6){
        cout << -2.0 << nL;
        return 0;
    }
    cout << ans << "\n";
    
    return 0;
}
