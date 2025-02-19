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

#define double long double

template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	bool operator<(R p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
    P cross(P a, P b) {
        return (a-*this).cross(b-*this);
    }
	T dist2() const { return x*x + y*y + z*z; }
	double dist() const { return sqrt((double)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	double phi() const { return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	double theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P rotate(double angle, P axis) const {
		double s = sin(angle), c = cos(angle); P u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
};

typedef Point3D<ld> P3;
const double eps = 1e-6;

vector<array<int, 3>> convex_shell(vector<P3> &p) {
	int n = sz(p);
	if(n < 3) return {};
	vector<array<int, 3>> faces;

	vvi active(n, vi(n, false));

	auto add_face = [&](int a, int b, int c) -> void {
		faces.push_back({a, b, c});
		active[a][b] = active[b][c] = active[c][a] = true;
	};

	add_face(0, 1, 2);
	add_face(0, 2, 1);

	rep(i, 3, n) {
		vector<array<int, 3>> new_faces;
		for(auto [a, b, c]: faces)
			if((p[i] - p[a]).dot(p[a].cross(p[b], p[c])) > eps)
				active[a][b] = active[b][c] = active[c][a] = false;
			else new_faces.push_back({a, b, c});
		faces.clear();
		for(array<int, 3> f: new_faces)
			rep(j, 0, 3) if(!active[f[(j+1)%3]][f[j]])
				add_face(f[(j+1)%3], f[j], i);
		faces.insert(end(faces), all(new_faces));
	}

	return faces;
}

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

typedef Point<double> P;
double ccRadius(const P& A, const P& B, const P& C) {
	return (B-A).dist()*(C-B).dist()*(A-C).dist()/
			abs((B-A).cross(C-A))/2;
}
P ccCenter(const P& A, const P& B, const P& C) {
	P b = C-A, c = B-A;
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}

pair<P, double> mec(vector<P> ps) {
	shuffle(all(ps), mt19937(time(0)));
	P o = ps[0];
	double r = 0, EPS = 1 + 1e-8;
	rep(i,0,sz(ps)) if ((o - ps[i]).dist() > r * EPS) {
		o = ps[i], r = 0;
		rep(j,0,i) if ((o - ps[j]).dist() > r * EPS) {
			o = (ps[i] + ps[j]) / 2;
			r = (o - ps[i]).dist();
			rep(k,0,j) if ((o - ps[k]).dist() > r * EPS) {
				o = ccCenter(ps[i], ps[j], ps[k]);
				r = (o - ps[i]).dist();
			}
		}
	}
	return {o, r};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n; cin >> n;
	vector<P3> pts(n);
	rep(i, 0, n) {
		cin >> pts[i].x >> pts[i].y >> pts[i].z;
	}
	auto faces = convex_shell(pts);
	double ans = 1e18;
	for(auto [i, j, k] : faces) {
		swap(i, k);
		P3 norm = pts[i].cross(pts[j], pts[k]);
		P3 ax1 = pts[j] - pts[i];
		P3 ax2 = norm.cross(ax1);
		double h = 0;
		vector<P> plane;
		rep(o, 0, n) {
			double z = norm.dot(pts[o] - pts[i]) / norm.dist();
			double x = ax1.dot(pts[o] - pts[i]) / ax1.dist();
			double y = ax2.dot(pts[o] - pts[i]) / ax2.dist();
			h = max(h, z);
			plane.push_back(P{x, y});
		}
		auto [center, r] = mec(plane);
		ans = min(ans, h * acos(-1) * r * r);
	}
	cout << fixed << setprecision(8) << ans << "\n";
    return 0;
}
