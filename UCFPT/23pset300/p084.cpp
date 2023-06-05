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
    int n; cin >> n;

    vector<P> v(n), v2;
    rep(i, 0, n){
        cin >> v[i].x >> v[i].y;
        v2.pb(Point(v[i].x, v[i].y));
    }
    vi inarray(n, 1);
    ll a = 0, b = 0;
    rep(i, 0, n - 2){
        ll mindex = -1, minarea = LLONG_MAX;
        rep(j, 0, sz(v)){
            int pre = j > 0 ? j - 1 : sz(v) - 1, post = j + 1 < sz(v) ? j + 1 : 0;
            ll area = v[j].cross(v[post], v[pre]); assert(area >= 0);
            if(area < minarea){
                mindex = j, minarea = area;
            }
        }
        (i % 2 == 0 ? a : b) += minarea;
        v.erase(v.begin() + mindex);
    }
    v = v2;
    bool alberto = a <= b;
    ll me = 0, you = 0;
    auto query = [&]()->void{
        ll mindex = -1, minarea = LLONG_MAX;
        rep(j, 0, sz(v)){
            int pre = j ? j - 1 : sz(v) - 1, post = j + 1 < sz(v) ? j + 1 : 0;
            ll area = v[j].cross(v[post], v[pre]); assert(area >= 0);
            if(area < minarea){
                mindex = j, minarea = area;
            }
        }
        int idx = -1, sum = 0;
        rep(i, 0, n){
            sum += inarray[i];
            if(sum == mindex + 1){
                idx = i; break;
            }
        }
        assert(idx != -1);
        assert(inarray[idx]);
        inarray[idx] = 0;
        me += minarea;
        v.erase(v.begin() + mindex);
        cout << (idx + 1) << endl;
        cout.flush();
    };
    auto getquery = [&]()->void{
        int k; cin >> k;
        k--;
        assert(inarray[k]);
        int sum = 0;
        rep(i, 0, k){
            sum += inarray[i];
        }
        inarray[k] = 0;
        int pre = sum == 0 ? sz(v) - 1 : sum - 1;
        int post = sum == sz(v) - 1 ? 0 : sum + 1;
        you += v[sum].cross(v[post], v[pre]);
        v.erase(v.begin() + sum);
    };
    cout << (alberto ? "Alberto" : "Beatrice") << "\n";
    cout.flush();
    bool turn = alberto;
    rep(i, 0, n - 2){
        if(turn) query();
        else getquery();
        turn ^= 1;
    }
    // assert(me <= you);
    // cout << me << " " << you << "\n";

    
    return 0;
}
