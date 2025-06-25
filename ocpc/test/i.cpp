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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
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
    bool side() const {
        return !(y > 0 || (y == 0 && x > 0));
    }
    bool operator<(P p) const { 
        if(side() != p.side()) return side() < p.side();
        return cross(p) > 0;
    }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

using P = Point<ll>;

struct FT {
	vector<P> s;
	FT(int n) : s(n) {}
	void update(int pos, P dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] = s[pos] + dif;
	}
	P query(int pos) { // sum of values in [0, pos)
		P res;
		for (; pos > 0; pos &= pos - 1) res = res + s[pos-1];
		return res;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vector<tuple<P, int, int, int>> events; 
    // dir, type, p/q id, index
    // 0 is change point event
    // 1 is query, query idx, mult
    vector<vector<P>> ps;
    FT ft(n);
    vector<P> inft(n);
    rep(pid, 0, n) {
        int k; cin >> k;
        vector<P> p(k);
        rep(i, 0, k) cin >> p[i].x >> p[i].y;
        P mn(p[0]);
        rep(i, 0, k) {
            if(p[i].y < mn.y) mn = p[i];
            events.push_back({p[(i+1)%k]-p[i], 0, pid, (i+1)%k});
        }
        ps.push_back(p);
        inft[pid] = mn;
        ft.update(pid, mn);
    }
    vector<P> bank(q), dir(q), made(q);
    vi ql(q), qr(q);
    rep(qid, 0, q) {
        ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        dir[qid] = P(x2-x1, y2-y1);
        cin >> bank[qid].x >> bank[qid].y;
        cin >> ql[qid] >> qr[qid]; ql[qid]--;
        if(bank[qid].perp().dot(dir[qid]) < 0) bank[qid] = bank[qid] * -1;
        events.push_back(tuple{bank[qid], 1, qid, -1});
        events.push_back(tuple{bank[qid] * -1, 1, qid, 1});
    }
    sort(all(events));
    for(auto [d, t, id, v] : events) {
        if(t == 0) {
            ft.update(id, inft[id] * -1);
            inft[id] = ps[id][v];
            ft.update(id, inft[id]);
        } else {
            made[id] = made[id] + (ft.query(qr[id]) - ft.query(ql[id])) * v;
        }
    }
    rep(qid, 0, q) {
        bank[qid] = bank[qid].perp();
        // cerr << "qid: " << qid << " " << bank[qid] << " " << dir[qid] << " " << made[qid] << endl;
        if(made[qid].dot(bank[qid]) >= dir[qid].dot(bank[qid])) cout << "YES\n";
        else cout << "NO\n";
    }



    
    return 0;
}
