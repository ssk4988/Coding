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
using P = Point<ll>;

const ll MOD = 1e9 + 3;
inline ll mod(ll k) {
    return (k % MOD + MOD) % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<P> pts(n);
    rep(i, 0, n){
        cin >> pts[i].x >> pts[i].y;
    }
    ll area = 0;
    ll concave = 0;
    rep(i, 0, n){
        rep(j, 0, i){
            auto p1 = pts[i], p2 = pts[j];
            vector<P> pos, neg;
            ll posa = 0, nega = 0;
            rep(k, 0, n){
                if(i == k || j == k) continue;
                if(p1.cross(p2, pts[k]) > 0){
                    pos.pb(pts[k]);
                    posa = mod(posa + abs(p1.cross(p2, pts[k])));
                }
                if(p1.cross(p2, pts[k]) < 0){
                    neg.pb(pts[k]);
                    nega = mod(nega + abs(p1.cross(p2, pts[k])));
                }
            }
            P ref = p1;
            auto cmp = [&](P a, P b) -> bool {
                return ref.cross(a, b) > 0;
            };
            area = mod(area + posa * sz(neg) + nega * sz(pos));
            sort(all(pos), cmp);
            sort(all(neg), cmp);
            ll sd = 0;
            // reverse(all(neg));
            int pnt = 0;
            for(auto p : pos){
                while(pnt < sz(neg) && p1.cross(p, neg[pnt]) > 0){
                    sd += abs(p1.cross(p2, neg[pnt]));
                    sd = mod(sd);
                    pnt++;
                }
                concave += sd;
                concave = mod(concave);
            }
            sd = 0;
            pnt = 0;
            ref = p2;
            sort(all(pos), cmp);
            sort(all(neg), cmp);
            reverse(all(neg));
            reverse(all(pos));
            for(auto p : pos){
                while(pnt < sz(neg) && p2.cross(p, neg[pnt]) < 0){
                    sd += abs(p1.cross(p2, neg[pnt]));
                    sd = mod(sd);
                    pnt++;
                }
                concave += sd;
                concave = mod(concave);
            }
        }
    }
    area = mod(area + concave);
    area = mod(area * ll(5e8+2));
    cout << area << "\n";
    
    return 0;
}
