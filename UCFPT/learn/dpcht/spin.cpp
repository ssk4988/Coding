#include <bits/stdc++.h>
using namespace std;

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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
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

template<class P> vector<P> convex_hull(vector<P> pts){
	if(sz(pts) == 1) return pts;
	stable_sort(all(pts));
	vector<P> hull(sz(pts)+1);
	int k = 0, t = 2;
	rep(_, 0, 2) {
		for(P p: pts){
			while(k >= t && hull[k-2].cross(hull[k-1], p) <= 0) k--;
			hull[k++] = p;
		}
		reverse(all(pts));
		t = k+1;
	}
	hull.resize(k-1);
	return hull;
}

#define cmp(i, j) p.cross(h[i], h[j == n ? 0 : j]) * (R ? 1 : -1)
template<bool R, class P> int getTangent(vector<P>& h, P p) {
	int n = sz(h), lo = 0, hi = n - 1, md;
	if (cmp(0, 1) >= R && cmp(0, n - 1) >= !R) return 0;
	while (md = (lo + hi + 1) / 2, lo < hi) {
		auto a = cmp(md, md + 1), b = cmp(md, lo);
		if (a >= R && cmp(md, md - 1) >= !R) return md;
		if (cmp(lo, lo + 1) < R)
			a < R&& b >= 0 ? lo = md : hi = md - 1;
		else a < R || b <= 0 ? lo = md : hi = md - 1;
	}
	return -1; // point strictly inside hull
}
template<class P> pii hullTangents(vector<P>& h, P p) {
	return {getTangent<0>(h, p), getTangent<1>(h, p)};
}
template<class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

template<class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
	auto a = (e-s).cross(p-s);
	double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}   
template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
using P = Point<ll>;
bool inHull(const vector<P>& l, P p, bool strict = true) {
	int a = 1, b = sz(l) - 1, r = !strict;
	if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
	if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
		return false;
	while (abs(a - b) > 1) {
		int c = (a + b) / 2;
		(sideOf(l[0], l[c], p) > 0 ? b : a) = c;
	}
	return sgn(l[a].cross(l[b], p)) < r;
}
int getSide(P p) {
    return (p.y > 0 || (p.y == 0 && p.x >= 0));
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<P> pts(n);
    vector<P> hull;
    rep(i, 0, n) {
        cin >> pts[i].x >> pts[i].y;
        int t; cin >> t;
        if(t) hull.pb(pts[i]);
    }
    hull = convex_hull(hull);
    // for(auto p : hull) cerr << p.x << " " << p.y << endl;
    if(sz(hull) == 1) {
        cout << "1\n";
        return 0;
    }
    if(sz(hull) == 2) {
        int in = 0;
        for(auto p : pts) {
            if(onSegment(hull[0], hull[1], p)) in++;
        }
        cout << in << "\n";
        return 0;
    }
    using ev = pair<P, int>;
    // {direction, -1 if add else 1}
    vector<ev> events;
    int in = 0;
    auto evcmp = [&](ev a, ev b) -> bool {
        ll v = a.f.cross(b.f);
        if(v > 0) return true;
        if(v < 0) return false;
        return a.s < b.s;
    };
    int inside = 0;
    for(auto p : pts) {
        if(inHull(hull, p, false)){
            // cerr << p.x << " " << p.y << " in hull" << endl;
            in++;
            inside++;
            continue;
        }
        auto [left, right] = hullTangents(hull, p);
        array<ev, 2> evs{ev{hull[left] - p, 1}, ev{hull[right] - p, -1}};
        for(auto &[d, dt] : evs) {
            assert(d.x != 0 || d.y != 0);
            if(!getSide(d)) d = d * -1;
            assert(getSide(d));
        }
        if(evcmp(evs[0], evs[1])) {
            // remove before add
            in++;
            // cerr << "rembeforeadd" << endl;
        }
        // cerr << p.x << " " << p.y << " addding events" << endl;
        for(auto ev : evs) events.pb(ev);
    }
    // cerr << "in: " << in << endl;
    int ans = in;
    sort(all(events), evcmp);
    rep(i, 0, sz(events)) {
        auto [d, dt] = events[i];
        // cerr << d.x << " " << d.y << " " << dt << endl;
        if(dt == -1) {
            bool firstadd = i == 0;
            if(i) {
                auto [nd, ndt] = events[i-1];
                if(nd.cross(d) != 0) firstadd = true;
            }
            if(firstadd) ans = min(ans, in);
        }
        in -= dt;
        assert(in >= inside);
        if(dt == 1) {
            ans = min(ans, in);
        }
    }
    cout << ans << "\n";
    
    return 0;
}
