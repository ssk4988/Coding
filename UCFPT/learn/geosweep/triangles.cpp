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
	bool operator<(P p) const { 
        if(sgn() != p.sgn()) return sgn() < p.sgn();
        return cross(p) > 0;
        // return tie(x,y) < tie(p.x,p.y); 
    }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
    bool sgn() const { return y == 0 ? x >= 0 : y > 0; }
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
    while(true){
        cin >> n;
        if(n == 0) break;
        vector<P> ps(n);
        rep(i, 0, n){
            cin >> ps[i].x >> ps[i].y;
        }
        vector<pair<P, pi>> angles;
        rep(i, 0, n){
            rep(j, 0, n){
                if(i == j) continue;
                angles.emplace_back((ps[j] - ps[i]).perp().perp().perp(), pi{i, j});
            }
        }
        vi perm(n); // what index in order is ps[i]


        P start(-1, 0);
        vector<P> order(ps);
        sort(all(order), [&](P a, P b)-> bool{
            // int s = sgn(start.dot(a) * start.dot(a) * b.dist2() - start.dot(b) * start.dot(b) * a.dist2());
            if(a.x != b.x) return a.x > b.x;
            return a.y < b.y;
        });
        rep(i, 0, n){
            // cout << order[i] << "\n";
            rep(j, 0, n){
                if(ps[i] == order[j]){
                    perm[i] = j;
                }
            }
        }
        ll smallest = LLONG_MAX, largest = 0; // store area * 2
        sort(all(angles));
        for(auto [dir, p] : angles){
            // cout << dir << " " << p.f << " " << p.s << "\n";
            auto [i1, i2] = p;
            int mindex = min(perm[i1], perm[i2]), maxdex = max(perm[i1], perm[i2]);
            if(dir.perp().dot(order[mindex]) > dir.perp().dot(order[maxdex])){ // fix inversions
                swap(order[perm[i1]], order[perm[i2]]);
                swap(perm[i1], perm[i2]);
            }
            if(maxdex + 1 < n){
                smallest = min(smallest, abs(order[perm[i1]].cross(order[perm[i2]], order[maxdex + 1])));
                largest = max(largest, abs(order[perm[i1]].cross(order[perm[i2]], order[n-1])));
            }
            if(mindex - 1 >= 0){
                smallest = min(smallest, abs(order[perm[i1]].cross(order[perm[i2]], order[mindex - 1])));
                largest = max(largest, abs(order[perm[i1]].cross(order[perm[i2]], order[0])));
            }
        }
        cout << fixed << setprecision(1) << ld(smallest) / 2 << " " << ld(largest) / 2 << "\n";
    }
    
    return 0;
}
