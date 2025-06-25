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

/*
sum of P dx + Q dy = integral over area of dQ/dx - dP/dy
Q = x
P = 0

sum over circumference of 0dx + xdy
given radius r
cos 2t = cos^2 t - sin^2 t = 2cos^2 t - 1

y = r sin t
dy/dt = r cos t
dy = r cos t dt
integral for t=0 to 2pi of (cx + r cos t) r cos t dt
= (r^2 cos^2 t + cx r cos t) dt = (r^2 (cos 2t + 1) / 2 + cx r cos t) dt
= (r^2/2 cos 2t + r^2/2) + (cx r cos t) dt


integrate to get r^2/4 sin 2t + r^2t/2 + cx r sin t for 0 to 2pi
*/

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
using Pd = Point<ld>;

bool circleInter(Pd a,Pd b,double r1,double r2,pair<Pd, Pd>* out) {
	if (a == b) { assert(r1 != r2); return false; }
	Pd vec = b - a;
	double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum*sum < d2 || dif*dif > d2) return false;
	Pd mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	*out = {mid + per, mid - per};
	return true;
}
ld eval(ld r, ld cx, ld t) {
	return r * r * (sin(2 * t) / 4 + t / 2) + cx * r * sin(t);
}

array<ld, 2> operator+(array<ld, 2> l, array<ld, 2> r) {
	array<ld, 2> res;
	rep(i, 0, 2) res[i] = l[i] + r[i];
	return res;
}

struct Node {
	int lo, hi;
	Node *l=0, *r=0;
	array<ld, 2> res;
	int lz = 0;
	Node() { res[0] = res[1] = 0; }
	Node(vd &x, ld rad, ld cx, int lo, int hi) : lo(lo), hi(hi) {
		if(lo + 1 < hi) {
			int mid = lo + (hi-lo) / 2;
			l = new Node(x, rad, cx, lo, mid), r = new Node(x, rad, cx, mid, hi);
			res = l->res + r->res;
			// cerr << lo << " " << hi << " " << res[1] << endl;
		} else {
			res[0] = eval(rad, cx, hi == sz(x) ? acosl(-1) : x[hi]) - eval(rad, cx, x[lo]);
			// res[0] = -res[1];
			res[1] = 0;
			// cerr << "leaf " << lo << " " << hi << " " << res[1] << endl;
		}
	}
	void toggle(int L, int R) {
		if(R <= lo || hi <= L) return;
		if(L <= lo && hi <= R) {
			swap(res[0], res[1]);
			lz = !lz;
			return;
		}
		push(), l->toggle(L, R), r->toggle(L, R);
		res = l->res + r->res;
	}
	void push() {
		if(lz) {
			l->toggle(lo, hi), r->toggle(lo, hi), lz = 0;
		}
	}
};
const ld eps = 1e-8;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
	int n; cin >> n;
	vector<P> c(n);
	vector<Pd> cd(n);
	vl r(n);
	vi dup(n, -1);
	rep(i, 0, n) {
		cin >> c[i].x >> c[i].y >> r[i];
		cd[i].x = c[i].x;
		cd[i].y = c[i].y;
	}
	rep(i, 0, n) {
		rep(j, 0, i+1) {
			if(c[j] == c[i] && r[j] == r[i]) {
				dup[i] = j;
				break;
			}
		}
	}
	vector<vd> inters(n);
	vector<Node> trees(n);
	rep(i, 0, n) {
		if(dup[i] != i) continue;
		rep(j, 0, n) {
			if(c[i] == c[j]) continue;
			pair<Pd, Pd> inter;
			if(!circleInter(cd[i], cd[j], r[i], r[j], &inter)) continue;
			inters[i].push_back((inter.f - cd[i]).angle());
			inters[i].push_back((inter.s - cd[i]).angle());
		}
		inters[i].push_back(-acosl(-1));
		inters[i].push_back(acosl(-1));
		sort(all(inters[i]));
		// rep(j, 0, sz(inters[i])) {
			// cerr << i << ": " << inters[i][j] << endl;
		// }
		trees[i] = Node(inters[i], r[i], c[i].x, 0, sz(inters[i]));
	}
	vi on(n, 0);
	rep(i, 0, n) {
		trees[dup[i]].toggle(0, sz(inters[dup[i]]));
		on[dup[i]] ^= 1;
		rep(j, 0, n) {
			if(dup[i] == dup[j]) continue;
			if(dup[j] != j) continue;
			int k = dup[j];
			if((c[i] - c[k]).dist() + r[k] <= r[i] + eps) {
				trees[k].toggle(0, sz(inters[k]));
				continue;
			}
			pair<Pd, Pd> inter;
			if(!circleInter(cd[i], cd[k], r[i], r[k], &inter)) continue;
			Pd on = cd[k] + (cd[i] - cd[k]).unit() * r[k];
			if(cd[k].cross(inter.f, on) < 0) swap(inter.f, inter.s);
			int l = lower_bound(all(inters[k]), (inter.f - cd[k]).angle() - eps) - begin(inters[k]);
			int r = lower_bound(all(inters[k]), (inter.s - cd[k]).angle() - eps) - begin(inters[k]);
			if(l <= r) trees[k].toggle(l, r);
			else trees[k].toggle(0, l), trees[k].toggle(r, sz(inters[i]));
			// cerr << i << " toggles " << k << " range " << l << "," << inters[k][l] << " to " << r << "," << inters[k][r] << endl;
		}
		ld ans = 0;
		rep(j, 0, i+1) {
			if(on[j]) ans += trees[j].res[1] - trees[j].res[0];
		}
		// rep(j, 0, n) 
		// cerr << "tree " << j << ": add " << trees[j].res[1] << " other " << trees[j].res[0] << endl;
		// cerr << "ans for i=" << i << endl;
		cout << fixed << setprecision(6) << ans << "\n";
	}

    return 0;
}
