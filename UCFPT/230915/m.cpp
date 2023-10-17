#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = float;
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
    const ld PI = acosl(-1);
    // cout << ;
    rep(cn, 0, nc){
        ld r, n, l; cin >> r >> n >> l;
        ld a =  l / 2 / tanl(PI / n) * l / 2 * n + PI * r * r + n * l * r;
        cout << fixed << setprecision(8) << a << nL;
    }
    
    return 0;
}
