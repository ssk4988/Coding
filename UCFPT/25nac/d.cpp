#include <bits/stdc++.h>
using namespace std;

#define int long long

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    int w, h; cin >> w >> h;
    vii ce(n), fl(m);
    rep(i, 0, n) {
        cin >> ce[i].f >> ce[i].s;
    }
    rep(i, 0, m) {
        cin >> fl[i].f >> fl[i].s;
    }
    auto calc = [&](vii &l) -> vi {
        int prv = 1;
        int p = 0;
        vi res;
        rep(x, 0, w+1) {
            while(p+1 < sz(l) && l[p+1].f <= x) p++;
            prv--;
            if(l[p].f == x) {
                int inter = l[p].s;
                for(int i = p; i >= 0; i--) {
                    if(l[i].f < x) break;
                    inter = max(inter, l[i].s);
                }
                while(prv <= inter) prv += 2;
            }
            else {
                while(prv * (l[p+1].f - l[p].f) <= (l[p+1].s-l[p].s) * (x - l[p].f) + l[p].s * (l[p+1].f - l[p].f)) prv += 2;
            }
            res.push_back(prv);
        }
        return res;
    };
    vi afl = calc(fl);
    for(auto &[x, y] : ce) y *= -1;
    vi ace = calc(ce);
    for(auto &y : ace) y *= -1;
    bool works = true;
    rep(i, 0, w+1) {
        if(afl[i] > ace[i]) works = false;
    }
    if(works) {
        cout << afl.back() << " " << ace.back() << "\n";
    } else cout << "impossible\n";
    
    return 0;
}
