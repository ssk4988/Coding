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
    int n, k; cin >> n >> k;
    vi f(n);
    vector<vd> precomp(2, vd(n));
    rep(i, 0, n) cin >> f[i];
    const ld PI = acosl(-1);
    rep(j, 0, n){
        ld vx = 0, vy = 0;
        rep(i, 0, n){
            vx += f[i] * cosl(-2 * PI * i * j / n);
            vy += f[i] * sinl(-2 * PI * i * j / n);
        }
        precomp[0][j] = vx, precomp[1][j] = vy;
    }
    auto score = [&](ll v)->ld {
        ld mx = 0;
        f[k] = v;
        rep(j, 0, n){
            ld vx = precomp[0][j], vy = precomp[1][j];
            rep(i, k, k + 1){
                vx += f[i] * cosl(-2 * PI * i * j / n);
                vy += f[i] * sinl(-2 * PI * i * j / n);
            }
            mx = max(mx, vx * vx + vy * vy);
        }
        f[k] = 0;
        return mx;
    };
    ll lo = -1e9, hi = 1e9;
    while(lo + 15 < hi){
        ll mid1 = (lo + hi) / 2, mid2 = mid1 + 1;
        if(score(mid1) < score(mid2)) hi = mid2;
        else lo = mid1;
    }
    ld best = score(lo);
    for(ll t = lo ; t <= hi; t++) best = min(best, score(t));
    cout << fixed << setprecision(12) << sqrtl(best) << "\n";
    
    return 0;
}