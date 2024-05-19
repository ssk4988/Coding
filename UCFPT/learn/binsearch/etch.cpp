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
    rep(cn,0,nc){
        ld f1, f2, a, b, c; cin >> f1 >> f2 >> a >> b >> c;
        ld ans = 0;
        ld dif = 2e6;
        ld target = (f2 - f1) / f2 / f1;
        rep(i, 0, 50){
            ld t = ans + dif;
            ld comp = a * t + b * (1 - exp(-1 * c * t));
            if(comp < target) ans = t;
            dif /= 2;
        }
        cout << "Crystal #" << (cn+1) << ": " << fixed << setprecision(2) << ans << "\n\n";
    }
    
    return 0;
}
