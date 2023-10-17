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
    friend ostream& operator<<(ostream &os, P p) {
        os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    }
};

using P = Point3D<ld>;
const ld eps = 1e-9;
pair<bool, P> planeLineIntersection(P n, P p0, P s, P e){
    P dif = e - s;
    // if(fabs(n.dot(dif)) < eps) return {false, n};
    ld t = n.dot(p0 - s) / n.dot(dif);
    if(t < -eps || t > 1 + eps) return {false, n};

    return {true, s + dif * t};
}

bool pointInTriangle(P inter, vector<P> &t2){
    ld angles = 0;
    rep(l, 0, 3){
        ld s1 = (t2[l] - inter).dist(), s2 = (t2[(l + 1) % 3] - inter).dist(), s3 = (t2[l] - t2[(l + 1) % 3]).dist2();
        // angles += acosl((s3 - s2 * s2 - s1 * s1) / -2 / s1 / s2);
        angles += acosl((t2[l] - inter).dot(t2[(l + 1) % 3] - inter) / s1 / s2);
        // angles += asinl((t2[l] - inter).unit().cross((t2[(l + 1) % 3] - inter).unit()).dist());
    }
    if(fabs(angles - 2 * acosl(-1)) < eps){
        // cout << angles * 180 / acosl(-1) << " " << (i + 1) << " " << (j + 1) << " " << inter.x << " " << inter.y << " " << inter.z << nL;
        return true;
    }
    return false;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vector<P> ps(6);
    rep(i, 0, 6){
        cin >> ps[i].x >> ps[i].y >> ps[i].z;
    }
    vpi ans;
    rep(i, 1, 6){
        rep(j, i + 1, 6){
            vector<P> t1 = {ps[i], ps[j], ps[0]}, t2;
            rep(l, 1, 6){
                if(l != i && l != j) t2.pb(ps[l]);
            }
            P n = (t1[1] - t1[0]).cross(t1[2] - t1[0]);
            int hasinter = false;
            P inter;
            for(auto p : t2){
                assert(!pointInTriangle(p, t1));
            }
            rep(k, 0, 3){
                auto [w, p] = planeLineIntersection(n, t1[0], t2[k], t2[(k + 1) % 3]);
                // && pointInTriangle(p, t2)
                if(w && pointInTriangle(p, t1)){
                    hasinter++;
                    inter = p;
                }
            }
            // if(hasinter > 0) cout << "inters " << hasinter << "\n";
            if(hasinter == 1){
                ans.pb({1 + min(i, j), 1 + max(i, j)});
                // cout << ans.back().f << " " << ans.back().s << " " << inter << nL;
                //  << inter << nL;
                // cout << t1[0] << " " << t1[1] << " " << t1[2] << nL;
            }
        }
    }
    sort(all(ans));
    cout << sz(ans) << nL;
    for(auto [i, j] : ans){
        cout << i << " " << j << nL;
    }
    
    return 0;
}
