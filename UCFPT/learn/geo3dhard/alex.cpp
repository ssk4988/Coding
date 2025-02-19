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

template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T x, T y, T z) : x(x), y(y), z(z) {}
    explicit Point3D(T theta, T phi) {
        z = sin(phi);
        y = cos(phi) * sin(theta);
        x = cos(phi) * cos(theta);
    }
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
	ld dist() const { return sqrt((ld)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	ld phi() const { return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	ld theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P rotate(ld angle, P axis) const {
		ld s = sin(angle), c = cos(angle); P u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
};

typedef Point3D<ld> P;
const ld R = 6371;
P north(0, 0, 1);

const ld eps = 1e-9;
const ld DEGRAD = acosl(-1) / 180;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        ld lat1, long1, lat2, long2; cin >> lat1 >> long1 >> lat2 >> long2;
        lat1 *= DEGRAD, long1 *= DEGRAD, lat2 *= DEGRAD, long2 *= DEGRAD;
        P v1(long1, lat1), v2(long2, lat2);
        P norm = v1.cross(v2);
        P binorm1 = norm.cross(v1), binorm2 = v2.cross(norm);
        bool alex = binorm1.dot(north) > eps && binorm2.dot(north) > eps;
        ld ans = min((v1-north).dist(), (v2-north).dist());
        if(alex) {
            P proj = (north - norm * norm.dot(north) / norm.dist2()).unit();
            ans = min(ans, (proj-north).dist());
        }
        ans *= R;
        cout << (alex ? "Alex" : "Timothy") << "\n";
        cout << fixed << setprecision(6) << ans << "\n\n";
    }
    
    return 0;
}
