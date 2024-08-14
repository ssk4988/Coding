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
	ld dist() const { return sqrtl((ld)dist2()); }
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
    P rotate90(P axis) const {
		int s = 1, c = 0; P u = axis.unit();
		return u*dot(u) - cross(u);
	}
    P rotate90(P s, P e) const {
        P ref = *this - s, axis = e - s;
        return ref.rotate90(axis) + s;
    };
    friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << "," << p.z << ")"; }
};
using P = Point3D<ld>;
struct Prism {
    array<P, 8> corners;
    vector<P> pts;
    vvi transform{{4, 5, 0, 1, 6, 7, 2, 3}, {1, 5, 3, 7, 0, 4, 2, 6}, {2, 3, 6, 7, 0, 1, 4, 5}, {4, 0, 6, 2, 5, 1, 7, 3}};
    Prism(ll x, ll y, ll z) {
        rep(i, 0, 8){
            if(i & 1) corners[i].x = x;
            if(i & 2) corners[i].y = y;
            if(i & 4) corners[i].z = z;
        }
    }
    void print() {
        rep(i, 0, 8) {
            cout << i << " " << corners[i] << "\n";
        }
    }
    void rot(int dir) {
        // down, right, up, left
        int s, e;
        if(dir == 0) {
            s = 0, e = 1;
        } else if(dir == 1) s = 1, e = 3;
        else if(dir == 2) s = 3, e = 2;
        else s = 2, e = 0;
        P sp = corners[s], ep = corners[e];
        for(auto &p : corners){
            p = p.rotate90(sp, ep);
        }
        for(auto &p : pts) p = p.rotate90(sp, ep);
        array<P, 8> tempcorners;
        rep(i, 0, 8) {
            tempcorners[transform[(dir + 2)%4][i]] = corners[i];
        }
        corners = tempcorners;
    }
};
ld eps = 1e-8;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    cout << fixed << setprecision(2);
    // P a(-1, 2, 5), axis(0, 0, 1), s(1, 1, 1), e(1, 2, 1);
    // a = a.rotate90(s, e);
    // cout << a << "\n";
    rep(cn, 0, nc){
        ll x, y, z; cin >> x >> y >> z;
        Prism pr(x, y, z);
        // pr.print();
        // pr.rot(0);
        // pr.print();
        // pr.rot(2);
        rep(i, 0, 2){
            P p; cin >> p.x >> p.y >> p.z;
            pr.pts.pb(p);
        }
        if(pr.pts[0].z == z){
            pr.rot(0);
            pr.rot(0);
        } else if(pr.pts[0].z == 0){}
        else if(pr.pts[0].x == x) pr.rot(1);
        else if(pr.pts[0].y == y) pr.rot(2);
        else if(pr.pts[0].x == 0) pr.rot(3);
        else if(pr.pts[0].y == 0) pr.rot(0);
        assert(pr.pts[0].z < eps && abs(pr.pts[0].z) < eps);
        P ref = pr.pts[0];
        ld best = LDBL_MAX;
        auto bt = [&](int left, bool down, bool right, auto &&bt) -> void {
            if(pr.pts[1].z < eps && abs(pr.pts[1].z) < eps){
                best = min(best, (pr.pts[1] - ref).dist());
            }
            if(left == 0) return;
            rep(i, 0, 4){
                if(i % 2 == 0 && down != (i == 0)) continue;
                if(i % 2 == 1 && right != (i == 1)) continue;
                pr.rot(i);
                bt(left-1, down, right, bt);
                pr.rot((i + 2) % 4);
            }
        };
        rep(i, 0, 2)
            rep(j, 0, 2)
                bt(8, i, j, bt);
        cout << "Universe #" << (cn+1) << ": " << best << "\n";
    }
    
    return 0;
}
