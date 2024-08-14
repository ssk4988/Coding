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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define pb push_back
#define all(x) x.begin(), x.end()
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
	ld dist() const { return sqrtl((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

const ld eps = 1e-8;
typedef Point<ld> P;
struct HalfPlane {
	P s, e, d;
	HalfPlane(P s = P(), P e = P()): s(s), e(e), d(e - s) {}
	bool contains(P p) { return d.cross(p - s) > -eps; }
	bool operator<(HalfPlane hp) {
		if(abs(d.x) < eps && abs(hp.d.x) < eps) 
			return d.y > 0 && hp.d.y < 0;
		bool side = d.x < eps || (abs(d.x) <= eps && d.y > 0);
		bool sideHp = hp.d.x < eps || (abs(hp.d.x) <= eps && hp.d.y > 0);
		if(side != sideHp) return side;
		return d.cross(hp.d) > 0;
	}
	P inter(HalfPlane hp) {
		auto p = hp.s.cross(e, hp.e), q = hp.s.cross(hp.e, s);
		return (s * p + e * q) / d.cross(hp.d);
	}
};

vector<P> hpIntersection(vector<HalfPlane> hps) {
	sort(all(hps));
	int n = sz(hps), l = 1, r = 0;
	vector<HalfPlane> dq(n+1);
	rep(i, 0, n) {
		while(l < r && !hps[i].contains(dq[r].inter(dq[r-1]))) r--;
		while(l < r && !hps[i].contains(dq[l].inter(dq[l+1]))) l++;
		dq[++r] = hps[i];
		if(l < r && abs(dq[r].d.cross(dq[r-1].d)) < eps) {
			if(dq[r].d.dot(dq[r-1].d) < 0) return {};
			r--;
			if(dq[r].contains(hps[i].s)) dq[r] = hps[i];
		}
	}
	while(l < r - 1 && !dq[l].contains(dq[r].inter(dq[r-1]))) r--;
	while(l < r - 1 && !dq[r].contains(dq[l].inter(dq[l+1]))) l++;
	if(l > r - 2) return {};
	vector<P> poly;
	rep(i, l, r)
		poly.push_back(dq[i].inter(dq[i+1]));
	poly.push_back(dq[r].inter(dq[l]));
	return poly;
}

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}


double segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0L,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}

template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = sz(p);
	rep(i,0,n) {
		P q = p[(i + 1) % n];
		// if (onSegment(p[i], q, a)) return !strict;
		if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<P> p(n);
    rep(i, 0, n){
        cin >> p[i].x >> p[i].y;
    }
    ld ans = 0;
    rep(t, 0, n){
        vector<HalfPlane> hps;
        hps.emplace_back(P{1e9, -1e9}, P{1e9, 1e9});
        hps.emplace_back(P{1e9, 1e9}, P{-1e9, 1e9});
        hps.emplace_back(P{-1e9, 1e9}, P{-1e9, -1e9});
        hps.emplace_back(P{-1e9, -1e9}, P{1e9, -1e9});
        rep(i, 0, n){
            if(i == t) continue;
            P dir = p[i] - p[t];
            P mid = (p[i] + p[t]) / 2;
            dir = dir.perp();
            hps.emplace_back(mid, mid + dir);
        }
        vector<P> cell = hpIntersection(hps);
        rep(i, 0, sz(cell)){
            P s = cell[i], e = cell[(i+1)%sz(cell)];
            for(auto x : {s, e}){
                if(inPolygon(p, x, false)){
                    ans = max(ans, (x - p[t]).dist());
                }
            }
            rep(j, 0, n){
                P s1 = p[j], e1 = p[(j+1)%n];
                auto [cnt, inter] = lineInter(s, e, s1, e1);
                if(cnt != 1) continue;
                if(segDist(s1, e1, inter) > eps || segDist(s, e, inter) > eps) continue;
                ans = max(ans, (inter - p[t]).dist());
            }
        }
    }
    cout << fixed << setprecision(8) << ans << "\n";

    
    return 0;
}
