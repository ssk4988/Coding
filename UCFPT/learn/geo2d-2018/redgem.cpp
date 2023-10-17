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


#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"


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
	ld dist() const { return sqrt((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cosl(a)-y*sinl(a),x*sinl(a)+y*cosl(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P>
vector<pair<P, P>> tangents(P c1, ld r1, P c2, ld r2) {
	P d = c2 - c1;
	ld dr = r1 - r2, d2 = d.dist2(), h2 = d2 - dr * dr;
	if (d2 == 0 || h2 < 0)  return {};
	vector<pair<P, P>> out;
	for (ld sign : {-1, 1}) {
		P v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
		out.push_back({c1 + v * r1, c2 + v * r2});
	}
	if (h2 == 0) out.pop_back();
	return out;
}

template<class P>
vector<P> circleLine(P c, ld r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	ld s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	P h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}

typedef Point<ld> P;
const ld eps = 1e-9;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ld p, x, y, r;
	const ld pi = acosl(-1);
	while(true){
		cin >> n >> p >> x >> y >> r;
		P red(x, y); P o(0, 0);
		if(n == 0) break;
		vector<pair<ld, int>> events;
		rep(i, 0, n){
			ld x1, y1, r1; cin >> x1 >> y1 >> r1;
			P c(x1, y1);
			vector<pair<P, P>> tans = tangents(red, r, c, -r1);
			vector<P> points; // points on the circumference of purple
			bool samepoint = false;
			for(auto [s, e] : tans){
				if((e - s).dist() < eps){
					// same point
					// do stuff with perpendicular to centers
					P dif = (c - red).rotate(-pi/2);
					vector<P> inters = circleLine(o, p, s, s + dif);
					points.resize(2);
					bool did0 = false, did1 = false;
					for(P inter : inters){
						// is this the starting or ending intersection
						if((inter - s).dot(dif) > 0){
							points[0] = inter;
							did0 = true;
						}
						else{
							points[1] = inter;
							did1 = true;
						}
					}
					samepoint = true;
					assert(did0 && did1);
					break;
				}
				else{
					vector<P> inters = circleLine(o, p, s, e);
					for(P inter : inters){
						if((inter - s).dot(e - s) > 0){
							points.pb(inter);
						}
					}
				}
			}
			
			assert(sz(points) == 2);
			// make sure that the points are in correct order
			if(!samepoint && red.cross(points[0], points[1]) < 0) swap(points[0], points[1]);
			// points[1] to left of points[0]
			ld a1 = points[0].angle(), a2 = points[1].angle();
			if(a2 < a1){
                events.pb({a1, 1});
                events.pb({pi, -1});
                events.pb({-pi, 1});
                events.pb({a2, -1});
            }
            else{
                events.pb({a1, 1});
                events.pb({a2, -1});
            }
		}
		int cnt = 0;
		ld ans = 0;
		ld pre = -pi;
		events.pb({-pi, 0});
		events.pb({pi, 0});
		sort(all(events));
		for(auto [angle, inc] : events){
			ld dif = angle - pre;
			if(cnt == 0) ans += dif;
			cnt += inc;
			pre = angle;
		}
		cout << fixed << setprecision(4) << (ans / 2 / pi) << "\n";

	}
    
    return 0;
}
