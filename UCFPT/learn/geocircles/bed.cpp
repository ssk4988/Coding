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
    ld l, w, h, x, y, a; cin >> l >> w >> h >> x >> y >> a;
    a = a / 180 * acos(-1);
    ld x1 = x + h * cosl(a);
    ld y1 = y + h * sinl(a);
    ld eps = 0;
    bool works = x1 >= -eps && x1 <= w + eps && y1 >= -eps && y1 <= l + eps;
    cout << (works ? "YES" : "NO") << nL;
    
    return 0;
}