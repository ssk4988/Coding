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

using P = Point3D<double>;
const double eps = 1e-9;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    while(true) {
        int nc; cin >> nc;
        if(nc == 0) break;
        double ans = 0;
        rep(cn, 0, nc) {
            int n; cin >> n;
            vector<vector<P>> faces(n);
            rep(i, 0, n) {
                int k; cin >> k;
                faces[i].resize(k);
                rep(j, 0, k) {
                    cin >> faces[i][j].x >> faces[i][j].y >> faces[i][j].z;
                }
            }
            P ref = faces[0][0];
            rep(i, 0, n) {
                P norm = faces[i][0].cross(faces[i][1], faces[i][2]);
                // if((ref - faces[i][0]).dot(norm) < -eps) reverse(all(faces[i]));
                double h = fabs((ref - faces[i][0]).dot(norm.unit()));
                rep(j, 1, sz(faces[i])-1) {
                    ans += fabs(faces[i][0].cross(faces[i][j], faces[i][j+1]).dot(norm.unit())) * h / 6;
                }
            }
        }
        cout << fixed << setprecision(2) << ans << "\n";
    }
    
    return 0;
}
