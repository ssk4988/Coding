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
        vl xs, ys;
        vvi ps;
        rep(i, 0, 4){
            int x, y; cin >> x >> y;
            xs.pb(x);
            ys.pb(y);
            ps.pb({x, y, i});
        }
        sort(all(xs));
        sort(all(ys));
        sort(all(ps));
        rep(i, 0, 4){
            ps[i][2] = i;
            swap(ps[i][0], ps[i][1]);
        }
        sort(all(ps));
        ll ans = xs[1] - xs[0] + xs[3] - xs[2] + ys[1] - ys[0] + ys[3] - ys[2];
        if(xs[3] - xs[0] < ys[2] - ys[1]){
            ans += 2 * ((ys[2] - ys[1]) - (xs[3] - xs[0]));
        }
        else if(ys[3] - ys[0] < xs[2] - xs[1]) {
            ans += 2 * ((xs[2] - xs[1]) - (ys[3] - ys[0]));
        }
        if(max(ps[0][2], ps[1][2]) <= min(ps[2][2], ps[3][2]) || min(ps[0][2], ps[1][2]) >= max(ps[2][2], ps[3][2])) {
            ans += 2 * min(xs[2] - xs[1], ys[2] - ys[1]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
