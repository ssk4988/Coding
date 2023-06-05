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
	ld dist() const { return sqrt((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
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

typedef Point<ld> P;
bool circleInter(P a,P b,ld r1,ld r2,pair<P, P>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	P vec = b - a;
	ld d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}

using P = Point<ld>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<P> trees(n); vd rs(n);
    rep(i, 0, n){
        cin >> trees[i].x >> trees[i].y >> rs[i];
    }
    const ld pi = acosl(-1);
    ld b, d; cin >> b >> d; P o(0, 0);
    vector<pair<ld, int>> events;
    rep(i, 0, n){
        rs[i] += b;
        vector<pair<P, P>> tns = tangents(trees[i], rs[i], o, 0);
        assert(sz(tns) == 2);
        if(tns[0].f.dist() >= d){
            // circle intersection
            pair<P, P> res;
            if(circleInter(o, trees[i], d, rs[i], &res)){
                if(o.cross(res.f, res.str) < 0) swap(res.f, res.str);
                ld a1 = res.f.angle(), a2 = res.str.angle();
                if(a1 >= 0 && a2 < 0){
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
        }
        else{
            if(o.cross(tns[0].f, tns[1].f) < 0) swap(tns[0], tns[1]);
            ld a1 = tns[0].f.angle(), a2 = tns[1].f.angle();
            if(a1 >= 0 && a2 < 0){
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
    cout << fixed << setprecision(8) << (ans / 2 / pi) << "\n";

    
    return 0;
}
