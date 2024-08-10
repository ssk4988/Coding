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

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point
{
	typedef Point P;
	T x, y;
	explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
	bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
	P operator+(P p) const { return P(x + p.x, y + p.y); }
	P operator-(P p) const { return P(x - p.x, y - p.y); }
	P operator*(T d) const { return P(x * d, y * d); }
	P operator/(T d) const { return P(x / d, y / d); }
	T dot(P p) const { return x * p.x + y * p.y; }
	T cross(P p) const { return x * p.y - y * p.x; }
	T cross(P a, P b) const { return (a - *this).cross(b - *this); }
	T dist2() const { return x * x + y * y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this / dist(); } // makes dist()=1
	P perp() const { return P(-y, x); }		  // rotates +90 degrees
	P normal() const { return perp().unit(); }
	T slope() const { return y / x; }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const
	{
		return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}
	friend ostream &operator<<(ostream &os, P p)
	{
		return os << "(" << p.x << "," << p.y << ")";
	}
};
using P = Point<ld>;

struct RollbackUF
{
	vi e;
	vector<pi> st;
	int mx = 1;
	RollbackUF(int n) : e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t)
	{
		for (int i = time(); i-- > t;)
		{
			if(st[i].f == -1) mx = st[i].s;
			else e[st[i].first] = st[i].second;
		}
		st.resize(t);
	}
	bool join(int a, int b)
	{
		a = find(a), b = find(b);
		if (a == b)
			return false;
		if (e[a] > e[b])
			swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		st.push_back({-1, mx});
		e[a] += e[b];
		mx = max(mx, -e[a]);
		e[b] = a;
		return true;
	}
};

const ld eps = 1e-7;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int n;
	cin >> n;
	vector<P> v(n);
	rep(i, 0, n)
	{
		cin >> v[i].x >> v[i].y;
	}
	RollbackUF uf(n);
	rep(i, 0, n){
		rep(j, 0, n){
			if((v[i] - v[j]).dist2() <= 4 + eps) uf.join(i, j);
		}
	}
	int restart = uf.time();
	int ans = uf.mx + 1;
	rep(i, 0, n){
		vi idx;
		rep(j, 0, n){
			if((v[i] - v[j]).dist2() <= 16 + eps) {
				idx.pb(j);
				// cout << i << " " << j << endl;
			}
		}
		vector<P> centers;
		for(int j : idx){
			if(i == j) continue;
			P mid = (v[i] + v[j]) / 2;
			P dir = (v[j] - v[i]).perp().unit();
			ld left = sqrtl(max(0.0l, 4 - (mid - v[i]).dist2()));
			centers.pb(mid + dir * left);
			centers.pb(mid - dir * left);
		}
		for(P c : centers){
			for(int j : idx) {
				if((c - v[j]).dist2() <= 4 + eps) {
					uf.join(i, j);
				}
			}
			// cout << c << " " << (1 + uf.mx) << endl;
			ans = max(ans, 1 + uf.mx);
			uf.rollback(restart);
		}
	}
	cout << ans << "\n";

	return 0;
}
