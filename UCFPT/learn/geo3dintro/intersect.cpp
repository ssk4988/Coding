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

// #define f first
// #define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

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
template<typename P>
istream& operator>>(istream& o, P& p) {
    return o >> p.x >> p.y >> p.z;
}
using P = Point3D<ld>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        cout << "Data Set #" << (cn+1) << ":\n";
        P s, e, a, b, c; cin >> s >> e >> a >> b >> c;
        // cout << s.x << " " << s.y << "\n";
        P v = e - s;
        P n = (b - a).cross(c - a);
        if(v.dot(n) == 0){
            // parallel
            if(n.dot(a) == n.dot(s)){
                cout << "The line lies on the plane.\n";

            } else {
                cout << "There is no intersection.\n";
            }
            cout << "\n";
            continue;
        }
        ld tcoef = 0;
        ld tconst = 0;
        tcoef += n.x * (e.x - s.x);
        tconst += n.x * (s.x - a.x);
        tcoef += n.y * (e.y - s.y);
        tconst += n.y * (s.y - a.y);
        tcoef += n.z * (e.z - s.z);
        tconst += n.z * (s.z - a.z);
        ld t = (-tconst) / tcoef;
        P inter = s + v * t;
        cout << fixed << setprecision(1) << "The intersection is the point (" << inter.x << ", " << inter.y << ", " << inter.z << ").\n\n";
    }
    
    return 0;
}
