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

int sigcross(pl a, pl b){
    ll lprod = a.f * b.s, rprod = a.s * b.f;
    if(lprod > rprod) return 1;
    if(lprod == rprod) return 0;
    return -1;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll sy, a, b; cin >> sy >> a >> b;
    int n; cin >> n;
    vl l(n), r(n);
    vl pref(n);
    rep(i, 0, n){
        cin >> l[i] >> r[i];
        if(i > 0){
            pref[i] = pref[i - 1] + l[i] - r[i - 1];
        }
    }
    int q; cin >> q;
    rep(i, 0, q){
        ll x, y; cin >> x >> y;
        int leftinterval = -1;
        int lo = 0, hi = n;
        while(lo < hi){
            int mid = lo + (hi - lo) / 2;
            pl v1 = {r[mid] - x, 0 - y}, v2 = {a - r[mid], sy - 0};
            int sigc = sigcross(v1, v2);
            if(sigc <= 0){
                hi = mid;
            }
            else{
                lo = mid + 1;
            }
        }
        leftinterval = lo;
        // if lo == n there is none
        int rightinterval = -1;
        lo = -1, hi = n - 1;
        while(lo < hi){
            int mid = lo + (hi - lo + 1) / 2;
            pl v1 = {l[mid] - x, 0 - y}, v2 = {b - l[mid], sy - 0};
            int sigc = sigcross(v1, v2);
            if(sigc >= 0){
                lo = mid;
            }
            else{
                hi = mid - 1;
            }
        }
        rightinterval = lo;
        // if lo == -1 there is none
        if(rightinterval == -1 || leftinterval == n){
            // impossible
            cout << fixed << setprecision(8) << 0 << nL;
            continue;
        }
        ll comb = abs(sy) + y;
        ld leftint = x + (a - x) * ld(y) / comb, rightint = x + (b - x) * ld(y) / comb;
        // if(l[leftinterval])
        leftint = max(ld(l[leftinterval]), leftint), rightint = min(ld(r[rightinterval]), rightint);
        
        // cout << "for point [" << x << "," << y << "] left intersection is " << leftint << " and right is " << rightint << nL;
        // cout << "left interval: " << leftinterval << " right interval: " << rightinterval << nL;
        ll coveredarea = pref[rightinterval] - pref[leftinterval];
        // cout << "covered area: " << coveredarea << nL;
        ld ans = (rightint - leftint - coveredarea) / ld(y) * comb;
        cout << fixed << setprecision(8) << ans << nL;

    }

    
    return 0;
}