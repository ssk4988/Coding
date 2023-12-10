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
ld eps = 1e-8;
struct Circle {
    ll x, r;
    Circle(ll x, ll r) : x(x), r(r) {}
    ld eval(ld x1){
        // assert(x1 - eps )
        return sqrtl(r * r - (x - x1) * (x - x1));
    }
    ld leftarea(ld x1){
        ld y = eval(x1);
        ld theta = acosl((x - x1) / ld(r));
        return r * r * theta / 2 - y * (x - x1) / 2;
    }
    ld rightarea(ld x1){
        return r * r * acosl(-1) / 4 - leftarea(x1);
    }
    // c.x > x
    int intersect(Circle &c){
        // no intersection
        if(c.x - x > c.r) return 0;
        if(x >= c.x - c.r && r * r >= c.r * c.r - (c.x - x) * (c.x - x)){
            // c intersects my vertical line
            return 1;
        }
        if(x - r >= c.x - c.r){
            // full contained by c
            return 2;
        }
        else{
            // weird intersection
            return 3;
        }
    }
};

struct ConvexContainer{
    vector<Circle> cs;
    vd prefarea;
    vd inter;
    bool add(Circle &c){
        if(sz(cs) == 0){
            cs.pb(c);
            prefarea.pb(c.r * c.r * acosl(-1) / 4);
            inter.pb(c.x - c.r);
            return true;
        }
        Circle &b = cs.back();
        int inttype = b.intersect(c);
        if(inttype == 0) return false;
        if(inttype == 1){
            cs.pb(c);
            prefarea.pb(prefarea.back() + c.rightarea(b.x));
            inter.pb(c.x - c.r);
        }
        else if(inttype == 2){
        }
        else{
            ld interx = (c.r * c.r - b.r * b.r - (c.x * c.x - b.x * b.x)) / ld(2) / (b.x - c.x);
            cs.pb(c);
            prefarea.pb(prefarea.back() + c.r * c.r * acosl(-1) / 4 - b.rightarea(interx) - c.leftarea(interx));
            inter.pb(interx);
        }
        return true;
    }
    ld eval(ld x1){
        int lo = 0, hi = sz(cs) - 1;
        while(lo < hi){
            int mid = lo + (hi - lo + 1) / 2;
            if(inter[mid] <= x1){
                lo = mid;
            }
            else hi = mid - 1;
        }
        ??????
    }
    ld overlap(Circle &c){
        if(sz(cs) == 0) return 0;
        int lo = 0, hi = sz(cs);
        // min index where we are intersecting (not out)
        while(lo < hi){
            int mid = lo + (hi - lo) / 2;
            bool in = cs[mid].intersect(c) == 2;
            bool out = cs[mid].intersect(c) == 0;
            if(out){
                lo = mid + 1;
            }
            else hi = mid;
        }
        if(lo == sz(cs)) return 0; // no intersection
        ld area = prefarea.back();
        if(lo > 0) area -= prefarea[lo];
        int inttype = cs[lo].intersect(c);
        
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<ConvexContainer> st;
    rep(i, 0, n){
        ll x, r; cin >> x >> r;
        Circle c(x, r);

    }
    
    return 0;
}
