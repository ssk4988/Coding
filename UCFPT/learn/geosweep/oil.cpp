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

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

using P = Point<ll>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    using pp = pair<P, int>;
    using pv = pair<P, P>;
    vector<pp> v;
    vector<pv> v1;
    int n; cin >> n;
    // map<P, ll> l;
    map<P, int> getidx;
    vl l(n);
    rep(i, 0, n){
        ll x1, x2, y; cin >> x1 >> x2 >> y;
        if(x1 > x2) swap(x2, x1);
        if(x1 == x2) continue;
        l[i] = abs(x2 - x1);
        v.pb({P(x1, y), i});
        v.pb({P(x2, y), i});
        getidx[P(x1, y)] = i;
        getidx[P(x2, y)] = i;
        v1.pb({P(x1, y), P(x2, y)});
    }
    ll ans = 0;
    P ref;
    auto side = [](P a)->bool{
        if(a.y > 0) return true;
        if(a.y < 0) return false;
        return a.x >= 0;
    };
    auto cmp = [&](P a, P b)->bool{
        bool ab = side(a - ref), bb = side(b - ref);
        if(ab != bb) return ab < bb;
        return ref.cross(a, b) < 0;
    };
    auto cmpp = [&](pp a, pp b)->bool{
        if(cmp(a.f, b.f)) return true;
        if(ref.cross(a.f, b.f) == 0) return a.s < b.s;
        return false;
    };
    for(auto [p, idx] : v){
        vector<vector<pp>> a(2);
        ll base = l[idx];
        ans = max(ans, base);
        ref = p;
        // cout << "reference: " << p << nL;
        for(auto [p1, p2] : v1){
            if(p1.y == p.y) continue;
            if(!cmp(p1, p2)) swap(p1, p2);
            assert(getidx.count(p1));
            int idx1 = getidx[p1];
            a[side(p1 - ref)].pb({p1, -idx1 - 1});
            a[side(p2 - ref)].pb({p2, idx1});
        }
        sort(all(a[0]), cmpp);
        sort(all(a[1]), cmpp);
        // unordered_set<int> inset;
        rep(sidetype, 0, 2){
            int pnt = 0;
            base = l[idx];
            for(auto [p1, idx1] : a[sidetype]){
                if(idx1 < 0) {
                    idx1 = -idx1 - 1;
                    base += l[idx1];
                    // cout << "adding in " << p1 << nL;
                }
                else{
                    base -= l[idx1];
                    // cout << "removing " << p1 << nL;
                }
                while(pnt < sz(a[1 - sidetype]) && (ref.cross(p1, a[1 - sidetype][pnt].f) > 0 || (ref.cross(p1, a[1 - sidetype][pnt].f) == 0 && a[1 - sidetype][pnt].s < idx))){
                    auto [p2, idx2] = a[1 - sidetype][pnt];
                    if(idx2 < 0){
                        idx2 = -idx2 - 1;
                        base += l[idx2];
                    }
                    else base -= l[idx2];

                    pnt++;
                }
                ans = max(ans, base);
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
