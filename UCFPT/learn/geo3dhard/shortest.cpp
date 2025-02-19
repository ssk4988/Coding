#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// using ld = long double;
using ld = double;
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

template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T x, T y, T z) : x(x), y(y), z(z) {}
	bool operator<(R p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
    P cross(P a, P b) {
        return (a-*this).cross(b-*this);
    }
	T dist2() const { return x*x + y*y + z*z; }
	ld dist() const { return sqrt((ld)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	ld phi() const { return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	ld theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P rotate(ld angle, P axis) const {
		ld s = sin(angle), c = cos(angle); P u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
};

template<class T>
Point3D<T> spherical(T theta, T phi) {
	return Point3D{cos(phi) * cos(theta), cos(phi) * sin(theta), sin(phi)};
}

typedef Point3D<ld> P;
ostream& operator<<(ostream& os, P& p) {
	return os << "(" << p.x << "," << p.y << "," << p.z << ")";
}

const ld eps = 1e-9;
const ld R = 6370;
const ld pi = acos(-1);
const ld DEGRAD = pi / 180;

bool cmpeq(const P &a, const P &b) {
	return max({abs(a.x-b.x), abs(a.y-b.y), abs(a.z-b.z)}) < eps;
}

bool cmp(const P &a, const P &b) {
	if(cmpeq(a, b)) return false;
	return a < b;
}

bool inCircle(P &d, ld dot, P &x) {
	return d.dot(x) >= dot - eps;
}

// returns {point, direction vector}
pair<P, P> planeInter(P &n1, ld dot1, P &n2, ld dot2) {
	P norm = n1.cross(n2);
	P v1 = n1.cross(norm), v2 = n2.cross(norm);
	// P on = v1 + v2;
	P on = v1 * -dot2 / norm.dist2() + v2 * dot1 / norm.dist2();
	return {on, norm};
}

// returns points on 1st circle that intersect 2nd, range between them on 1st is in 2nd
optional<pair<P, P>> circleInter(P &d1, ld dot1, P &d2, ld dot2) {
	P norm = d1.cross(d2);
	// d1 and d2 can't be parallel
	if(norm.dist() < eps) return nullopt;
	norm = norm.unit();
	P edge = d1.rotate(acos(dot1), norm);
	// must not be far apart
	if(!inCircle(d2, dot2, edge)) return nullopt;
	P edge2 = d1.rotate(-acos(dot1), norm); // fully contained
	if(inCircle(d2, dot2, edge2)) return nullopt;
	P d1plane = d1 * dot1;
	auto [on, dir] = planeInter(d1, dot1, d2, dot2);
	P center = on - dir * (on-d1plane).dot(dir) / dir.dist2();
	ld dist = sqrt((edge-d1plane).dist2() - (center-d1plane).dist2());
	P dir2 = dir.unit() * dist;
	auto res = pair{center + dir2, center - dir2};
	if(d1.dot((res.first - d1plane).cross(res.second - d1plane)) < eps) swap(res.first, res.second);
	return res;
}

void solve(int original_n)
{
	ld airport_radius; cin >> airport_radius;
	airport_radius /= R;
	map<P, int, decltype(cmp)*> to_id(&cmp);
	vector<P> pts;
	rep(i, 0, original_n) {
		ld theta, phi; cin >> theta >> phi;
		theta *= DEGRAD, phi *= DEGRAD;
		P p = spherical(theta, phi);
		assert(!to_id.count(p));
		to_id[p] = sz(to_id);
		pts.push_back(p);
	}
	ld circle_dot = cosl(airport_radius);
	rep(i, 0, original_n) {
		rep(j, 0, i) {
			auto tmp = circleInter(pts[i], circle_dot, pts[j], circle_dot);
			if(!tmp) continue;
			auto [p1, p2] = *tmp;
			for(auto p : {p1, p2}) {
				if(!to_id.count(p)) {
					to_id[p] = sz(to_id);
					pts.push_back(p);
				}
			}
		}
	}
	int nodes = sz(pts);
	vector<vector<ld>> cost(nodes, vector<ld>(nodes, 1e18));
	rep(i, 0, nodes) {
		bool has_opp = to_id.count(pts[i]*-1);
		bool reach_opp = false;
		rep(j, 0, nodes) {
			if(i == j) continue;
			P oppj = pts[j] * -1;
			if(cmpeq(pts[i], oppj)) continue;
			P norm = pts[i].cross(pts[j]).unit();
			vector<pair<ld, int>> events;
			auto get_angle = [&](P &p) {
				ld angle = acos(clamp(pts[i].dot(p), -ld(1), ld(1))); // only works since plane is hemisphere
				if(pts[i].cross(p).dot(norm) < eps) angle = 2 * pi - angle; // flip if negative
				return angle;
			};
			ld target = get_angle(pts[j]);
			events.push_back({target, 0});
			events.push_back({pi, 0});
			events.push_back({0, 0});
			events.push_back({pi*2, 0});
			rep(k, 0, original_n) {
				auto tmp = circleInter(norm, 0, pts[k], circle_dot);
				if(!tmp) continue;
				auto [p1, p2] = *tmp;
				ld a1 = get_angle(p1), a2 = get_angle(p2);
				events.push_back({a1, 1});
				events.push_back({a2, -1});
				if(a1 <= a2 + eps) {}
				else {
					events.push_back({pi * 2, -1});
					events.push_back({0, 1});
				}
			}
			sort(all(events));
			ld uncover = 0, uncover1 = 0, uncover2 = 0, pre = 0;
			int t = 0;
			for(auto [x, dt] : events) {
				ld dx = x - pre;
				if(t == 0) {
					uncover += dx;
					if(x <= pi) uncover1 += dx;
					else uncover2 += dx;
				}
				if(x == target && uncover < eps) {
					cost[i][j] = min(cost[i][j], target);
				}
				t += dt;
				pre = x;
			}
			if(max(uncover1, uncover2) < eps && has_opp) reach_opp = true;
		}
		if(reach_opp) {
			int opp_idx = to_id[pts[i] * -1];
			cost[i][opp_idx] = min(cost[i][opp_idx], pi);
		}
	}
	rep(i, 0, nodes)
		rep(j, 0, nodes) cost[i][j] = min(cost[i][j], cost[j][i]);
	rep(i, 0, nodes) cost[i][i] = 0;
	rep(k, 0, nodes)
		rep(i, 0, nodes)
			rep(j, 0, nodes)
				cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
	int q; cin >> q;
	rep(qid, 0, q) {
		int s, t; cin >> s >> t; s--, t--;
		ld refuel; cin >> refuel;
		refuel /= R;
		vector<ld> dist(original_n, -1);
		priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<>> pq;
		pq.push({0, s});
		while(!pq.empty()){
			auto [d_u, u] = pq.top(); pq.pop();
			if(dist[u] != -1) continue;
			dist[u] = d_u;
			rep(v, 0, original_n) {
				if(cost[u][v] - eps < refuel) pq.push({d_u + cost[u][v], v});
			}
		}
		if(dist[t] == -1) cout << "impossible\n";
		else cout << fixed << setprecision(3) << dist[t]*R << "\n";
	}   
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
	int original_n;
	int cn = 1;
	while(cin >> original_n) {
		cout << "Case " << cn++ << ":\n";
		solve(original_n);
	}
}
