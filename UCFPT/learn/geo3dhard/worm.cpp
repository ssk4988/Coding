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

typedef Point3D<ll> P;
const double eps = 1e-6;

vector<array<int, 3>> convex_shell(vector<P> &p) {
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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    while(true){
        int n; cin >> n;
        if(n == 0) break;
        vector<P> pts(n);
        rep(i, 0, n) {
            cin >> pts[i].x >> pts[i].y >> pts[i].z;
        }
        auto faces = convex_shell(pts);
        int q; cin >> q;
        rep(_, 0, q) {
            double ans = 1e18;
            P c; cin >> c.x >> c.y >> c.z;
            for(auto [i,j,k] : faces) {
                swap(i, k);
                P norm = pts[i].cross(pts[j], pts[k]);
                ans = min(ans, norm.dot(c - pts[i]) / norm.dist());
            }
            cout << fixed << setprecision(4) << ans << "\n";
        }
    }
    
    return 0;
}
