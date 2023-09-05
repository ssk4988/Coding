#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

using vi = vector<int>;
using ll = long long;
using pi = pair<int, int>;
using ld = long double;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ld p, d; cin >> p >> d;
    ld rx, ry, rz, vx, vy, vz; cin >> rx >> ry >> rz >> vx >> vy >> vz;
    ld x, y, z; cin >> x >> y >> z;
    ld v = sqrtl(vx * vx + vy * vy + vz * vz);
    ld t = d / v;
    ld ans = 0;
    vx -= rx, vy -= ry, vz -= rz;
    // if(vx > 0){
        ans += fabs(vx) * y * z;
    // }
    ans += fabs(vy) * x * z;
    ans += fabs(vz) * x * y;

    ans *= p * t;
    cout << fixed << setprecision(8) << ans << "\n";
}
