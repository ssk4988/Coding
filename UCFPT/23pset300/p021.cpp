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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vector<P> c(n);
    unordered_map<ll, int> xcnt, ycnt;
    set<P> ss;
    rep(i, 0, n)
    {
        cin >> c[i].x >> c[i].y;
        xcnt[c[i].x]++;
        ycnt[c[i].y]++;
        ss.insert(c[i]);
    }
    for(auto [x, cnt] : xcnt){
        if(cnt > 1){
            rep(y, 0, 100){
                if(ycnt[y] == 0){
                    cout << x << " " << x << " " << 1 << " " << y << " " << y << " " << 1 << nL;
                    return 0;
                }
            }
            assert(false);
            return 0;
        }
    }
    for(auto [y, cnt] : ycnt){
        if(cnt > 1){
            rep(x, 0, 100){
                if(xcnt[x] == 0){
                    cout << x << " " << x << " " << 1 << " " << y << " " << y << " " << 1 << nL;
                    return 0;
                }
            }
            assert(false);
            return 0;
        }
    }
    sort(all(c));
    P dd = c[1] - c[0];
    if(dd.x != 0 && dd.y != 0){
        
    }
    assert(dd.x != 0 && dd.y != 0);
    dd = dd / gcd(abs(dd.x), abs(dd.y));
    ll d1 = dd.dist2();
    rep(s1, 0, 2){
        rep(s2, s1 + 1, 3){
            P dx = c[s2] - c[s1];
            P start = c[s1];
            set<P> xs, ys;
            xs.insert(start);
            while(ss.count(start + dx)){
                start = start + dx;
                xs.insert(start);
            }
            vector<P> notinx;
            rep(i, 0, n){
                if(!xs.count(c[i])){
                    notinx.pb(c[i]);
                }
            }
            P dy(0, 0);
            ll d2 = 0;
            if(sz(notinx) > 1){
                dy = notinx[1] - notinx[0];
                d2 = (notinx[1] - notinx[0]).dist2();
                rep(i, 2, sz(notinx)){
                    ll d3 = (notinx[i] - notinx[i - 1]).dist2();
                    d2 = __gcd(d2, d3);
                }
                if(d2 % d1 != 0){
                    continue;
                }
                else{
                    P start1 = notinx[0];
                    ll scale = ll(sqrtl(d2 / d1));
                    assert(scale * scale == d2 / d1);
                    P dy = dd * scale;
                    set<P> notinxset;
                    for(P p : notinx){
                        notinxset.insert(p);
                    }
                    if(notinxset.count(start1)){
                        notinxset.erase(start1);
                    }
                    while(ss.count(start1 + dy)){
                        start1 = start1 + dy;
                        if(notinxset.count(start1)){
                            notinxset.erase(start1);
                        }
                    }
                    if(notinxset.size() == 0){
                        cout << c[s1].x << " " << start.x << " " << dx.x << " " << notinx[0].y << " " << start1.y << " " << dy.y << nL;
                        return 0;
                    }
                }
            }
            else if(sz(notinx) == 1){
                cout << c[s1].x << " " << start.x << " " << dx.x << " " << notinx[0].y << " " << notinx[0].y << " " << 1 << nL;
                return 0;
            }
            else{
                cout << c[s1].x << " " << start.x << " " << dx.x << " " << c[0].y << " " << c[0].y << " " << 1 << nL;
                return 0;
            }
        }
    }
    assert(false);
    return 0;

    return 0;
}