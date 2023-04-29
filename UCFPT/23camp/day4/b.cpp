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
    ld pi = acos(-1);
    vector<ld> angles;
    rep(i, 0, n){
        int x, y; cin >> x >> y;
        ld angle;
        if(x == 0){
            angle = y > 0 ? pi / 2 : 3 * pi / 2;
        }
        else{
            angle = atan((ld)y / x);
            // cout << " atan: " << angle << " ";
            if(x <= 0 && y >= 0){
                angle += pi;
            }
            else if(x <= 0 && y <= 0){
                angle += pi;
            }
        }
        if(angle < 0){
            angle += 2 * pi;
        }
        // cout << "x: " << x << " Y: " << y << " angle: " << angle << nL;
        angles.pb(angle);
    }
    sort(all(angles));
    angles.pb(angles[0] + 2 * pi);
    ld maxans = 2 * pi;
    rep(i, 0, n){
        maxans = min(maxans, 2 * pi - abs(angles[i + 1] - angles[i]));
    }
    // maxans = min(maxans, abs(angles[0] + 2 * pi - angles[n - 1]));
    if(n == 1) maxans = 0;
    cout << fixed << setprecision(8) << 180 * maxans / pi << nL;
    
    return 0;
}