#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first 
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using ld = long double;

template<class T> struct Point3D{
    typedef Point3D P;
    typedef const P& R;
    T x, y, z;
    explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
    P operator+(R p) const { return P(x + p.x, y + p.y, z + p.z); }
    P operator-(R p) const { return P(x - p.x, y - p.y, z - p.z); }
    P operator*(T d) const { return P(x * d, y * d, z * d); }
    P operator/(T d) const { return P(x / d, y / d, z / d); }
    T dot(R p) const {return x * p.x + y * p.y + z * p.z; }
    P cross(R p) const{
        return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    T dist2() const{ return x * x + y * y + z * z; }
    ld dist() const {return sqrt((ld)dist2());}

    P unit() const{ return *this/(T)dist();}

    P rotate(ld angle, P axis) const{
        ld s = sinl(angle), c = cosl(angle); P u = axis.unit();
        return u*dot(u)*(1-c)+(*this)*c - cross(u)*s;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        Point3D<ld> a; cin >> a.x >> a.y >> a.z;
        Point3D<ld> p; cin >> p.x >> p.y >> p.z;
        ld deg; cin >> deg;
        deg = deg / 180 * acosl(-1);
        Point3D<ld> res1 = p.rotate(deg, a), res2 = p.rotate(-deg, a);
        Point3D<ld> ans = res1.z > res2.z ? res1 : res2;
        cout << fixed << setprecision(8) << ans.x << " " << ans.y << " " << ans.z << "\n";
    }
}
