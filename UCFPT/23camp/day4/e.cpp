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
using vvl = vector<vl>;

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

typedef vector<bitset<1000>> vb;
struct Maxclique {
	double limit=0.025, pk=0;
	struct Vertex { int i, d=0; };
	typedef vector<Vertex> vv;
	vb e;
	vv V;
	vector<vi> C;
	vi qmax, q, S, old;
	void init(vv& r) {
		for (auto& v : r) v.d = 0;
		for (auto& v : r) for (auto j : r) v.d += e[v.i][j.i];
		sort(all(r), [](auto a, auto b) { return a.d > b.d; });
		int mxD = r[0].d;
		rep(i,0,sz(r)) r[i].d = min(i, mxD) + 1;
	}
	void expand(vv& R, int lev = 1) {
		S[lev] += S[lev - 1] - old[lev];
		old[lev] = S[lev - 1];
		while (sz(R)) {
			if (sz(q) + R.back().d <= sz(qmax)) return;
			q.push_back(R.back().i);
			vv T;
			for(auto v:R) if (e[R.back().i][v.i]) T.push_back({v.i});
			if (sz(T)) {
				if (S[lev]++ / ++pk < limit) init(T);
				int j = 0, mxk = 1, mnk = max(sz(qmax) - sz(q) + 1, 1);
				C[1].clear(), C[2].clear();
				for (auto v : T) {
					int k = 1;
					auto f = [&](int i) { return e[v.i][i]; };
					while (any_of(all(C[k]), f)) k++;
					if (k > mxk) mxk = k, C[mxk + 1].clear();
					if (k < mnk) T[j++].i = v.i;
					C[k].push_back(v.i);
				}
				if (j > 0) T[j - 1].d = 0;
				rep(k,mnk,mxk + 1) for (int i : C[k])
					T[j].i = i, T[j++].d = k;
				expand(T, lev + 1);
			} else if (sz(q) > sz(qmax)) qmax = q;
			q.pop_back(), R.pop_back();
		}
	}
	vi maxClique() { init(V), expand(V); return qmax; }
	Maxclique(vb conn) : e(conn), C(sz(e)+1), S(sz(C)), old(S) {
		rep(i,0,sz(e)) V.push_back({i});
	}
};

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

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) // if parallel
		return {-(s1.cross(e1, s2) == 0), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}
ld dist(ld x1, ld y1, ld x2, ld y2){
    return sqrtl((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

ld eps = 1e-9;
bool intersectAtTime(Point<ld> s1, Point<ld> e1, Point<ld> s2, Point<ld> e2, Point<ld> inter, ll dt1, ll dt2, ll t1, ll t2, int type){
    // assume time of s1 < time of e1
    // ld dx1 = e1.x - s1.x;
    // ld dy1 = e1.y - s1.y;
    // ld dx2 = e2.x - s2.x;
    // ld dy2 = e2.y - s2.y;    
    if(abs(s1.x - e1.x) < eps && abs(s1.y - e1.y) < eps) return true;
    if(abs(s2.x - e2.x) < eps && abs(s2.y - e2.y) < eps) return true;
    ld lldx1 = abs(e1.x - s1.x);
    ld lldy1 = abs(e1.y - s1.y);
    ld lldx2 = abs(e2.x - s2.x);
    ld lldy2 = abs(e2.y - s2.y);
    ld intdx1 = abs(inter.x - s1.x);
    ld intdy1 = abs(inter.y - s1.y);
    ld intdx2 = abs(inter.x - s2.x);
    ld intdy2 = abs(inter.y - s2.y);
    ld d1 = lldx1 == 0 ? lldy1 : lldx1;
    ld d2 = lldx2 == 0 ? lldy2 : lldx2;
    ld id1 = lldx1 == 0 ? intdy1 : intdx1;
    ld id2 = lldx2 == 0 ? intdy2 : intdx2;
    if(type == -1){
        ld lowt = -1e6, hight = 1e6;
        while(abs(lowt - hight) > eps){
            ld midt1 = lowt + (hight - lowt) / 3;
            ld midt2 = lowt + 2 * (hight - lowt) / 3;
            ld x1 = s1.x + (e1.x - s1.x) / dt1 * midt1, x2 = s2.x + (e2.x - s2.x) / dt2 * midt1;
            ld y1 = s1.y + (e1.y - s1.y) / dt1 * midt1, y2 = s2.y + (e2.y - s2.y) / dt2 * midt1;
            ld x11 = s1.x + (e1.x - s1.x) / dt1 * midt2, x21 = s2.x + (e2.x - s2.x) / dt2 * midt2;
            ld y11 = s1.y + (e1.y - s1.y) / dt1 * midt2, y21 = s2.y + (e2.y - s2.y) / dt2 * midt2;
            if(dist(x1, y1, x2, y2) < dist(x11, y11, x21, y21)){
                hight = midt2;
            }
            else{
                lowt = midt1;
            }

        }
        ld x1 = s1.x + (e1.x - s1.x) / dt1 * lowt, x2 = s2.x + (e2.x - s2.x) / dt2 * lowt;
        ld y1 = s1.y + (e1.y - s1.y) / dt1 * lowt, y2 = s2.y + (e2.y - s2.y) / dt2 * lowt;
        return dist(x1, y1, x2, y2) < eps;
    }
    if(abs((t1 + id1 / d1 * dt1) - (t2 + id2 / d2 * dt2)) <= eps){
        return true;
    }
    return false;

}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // Point<ld> s1(0, 5), e1(2, 8), s2(0, 7), e2(1, -29);
    // pair<int, Point<ld>> inter = lineInter(s1, e1, s2, e2);
    int n; cin >> n;
    vector<vector<Point<ld>>> pts(n, vector<Point<ld>>(2));
    vvl t(n, vl(2));
    rep(i, 0, n){
        ll x1, y1, x2, y2;
        cin >> t[i][0] >> x1 >> y1 >> t[i][1] >> x2 >> y2;
        if(t[i][0] > t[i][1]){
            swap(t[i][0], t[i][1]);
            swap(x1, x2);
            swap(y1, y2);
        }
        pts[i][0] = Point<ld>(x1, y1);
        pts[i][1] = Point<ld>(x2, y2);
    }
    vvi adj(n);
    rep(i, 0, n){
        rep(j, i + 1, n){
            if(i == j) continue;
            pair<int, Point<ld>> res = lineInter(pts[i][0], pts[i][1], pts[j][0], pts[j][1]);
            if(res.f != 0){
                // cout << "intersect " << i << " " << j << nL;
                if(intersectAtTime(pts[i][0], pts[i][1], pts[j][0], pts[j][1], res.s, t[i][1] - t[i][0], t[j][1] - t[j][0], t[i][0], t[j][0], res.f)){
                    adj[i].pb(j);
                    adj[j].pb(i);
                    // cout << "correct time for " << i << " " << j << nL;
                }
            }
        }
    }
    vb adjb(n);
    rep(i, 0, n){
        for(int j : adj[i]){
            adjb[i][j] = 1;
        }
    }
    Maxclique nm(adjb);
    vi mcq = nm.maxClique();
    cout << mcq.size() << nL;


    return 0;
}