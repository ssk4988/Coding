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
        int n; cin >> n;
        vl xs(n), ys(n);
        rep(i, 0, n){
            cin >> xs[i] >> ys[i];
        }
        ll x, y; cin >> x >> y;
        ll x1, y1; cin >> x1 >> y1;
        bool works = true;
        ll dist2 = (x1 - x) * (x1 - x) + (y1 - y) * (y1 - y);
        rep(i, 0, n){
            if((x1 - xs[i]) * (x1 - xs[i]) + (y1 - ys[i]) * (y1 - ys[i]) <= dist2) works = false;
        }
        cout << (works ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
