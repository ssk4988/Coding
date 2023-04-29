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
        ld s, r; cin >> s >> r;
        ld pi = acos(-1);
        ld ans = 0;
        if(2 * r < s){
            ans = pi * r * r;
        }
        else if(2 * r >= s * sqrtl(2)){
            ans = s * s;
        }
        else{
            ld c = sqrtl(r * r - s * s / 4);
            ans += 2 * c * s;
            ans += 8 * pi * r * r * (pi / 4 - acos(s/2/r)) / 2 / pi;
        }
        cout << fixed << setprecision(2) << ans << nL;
    }
    
    return 0;
}