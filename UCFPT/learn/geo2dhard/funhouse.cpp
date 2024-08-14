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
;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    int side() {
        return y < 0 || (y == 0 && x < 0);
    }
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
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
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
using P = Point<ll>;

bool cmp(P a, P b) {
    if(a.side() != b.side()) return a.side() < b.side();
    return a.cross(b) > 0;
}

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
	return a;
}

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int e;
    while (true)
    {
        cin >> e;
        if (e == 0)
            break;
        vector<array<P, 2>> ep(e);
        vector<array<int, 2>> epid(e);
        vector<string> et(e);
        map<P, int> pid;
        vector<P> points;
        vvi used(e, vi(2));
        vvi pedges; // for each point, list of edge ids
        auto otherpoint = [&](int idx, int pid) -> int {
            return epid[idx][epid[idx][0] == pid];
        };
        rep(i, 0, e)
        {
            cin >> ep[i][0].x >> ep[i][0].y >> ep[i][1].x >> ep[i][1].y;
            cin >> et[i];
            rep(t, 0, 2)
            {
                if (!pid.count(ep[i][t]))
                {
                    pid[ep[i][t]] = sz(pid);
                    pedges.pb({});
                    points.pb(ep[i][t]);
                }
                pedges[pid[ep[i][t]]].pb(i);
                epid[i][t] = pid[ep[i][t]];
            }
        }
        int npoly = 0;
        vvi polypoints;
        vvi polyedges;
        rep(i, 0, e){
            rep(t, 0, 2){
                if(used[i][t]) continue;
                npoly++;
                polypoints.pb({});
                polyedges.pb({});
                polypoints.back().pb(epid[i][t]);
                polypoints.back().pb(epid[i][1-t]);
                polyedges.back().pb(i);
                used[i][t] = true;
                while(polypoints.back().back() != polypoints.back().front()){
                    int prvidx = polypoints.back()[sz(polypoints.back()) - 2];
                    int curidx = polypoints.back().back();
                    P dir = points[prvidx] - points[curidx];
                    int bestedge = -1;
                    for(int eid : pedges[curidx]) {
                        int nxtidx = otherpoint(eid, curidx);
                        if(nxtidx == prvidx) continue;
                        if(bestedge == -1) {
                            bestedge = eid;
                            continue;
                        }
                        int bestnxtidx = otherpoint(bestedge, curidx);
                        int nxtside = points[curidx].cross(points[prvidx], points[nxtidx]) <= 0;
                        int bestside = points[curidx].cross(points[prvidx], points[bestnxtidx]) <= 0;
                        if(nxtside < bestside) continue;
                        if(nxtside > bestside){
                            bestedge = eid;
                            continue;
                        }
                        if(points[curidx].cross(points[bestnxtidx], points[nxtidx]) >= 0){
                            bestedge = eid;
                            continue;
                        }
                    }
                    assert(bestedge != -1);
                    int nxtidx = otherpoint(bestedge, curidx);
                    polypoints.back().pb(nxtidx);
                    polyedges.back().pb(bestedge);
                    // assert(!used[bestedge][curidx == epid[bestedge][1]]);
                    used[bestedge][curidx == epid[bestedge][1]] = true;
                }
            }
        }
        Dinic d(2 * npoly + 2);
        int supersource = 2 * npoly, supersink = 2 * npoly + 1;
        // cout << "calc polys: " << npoly << endl;
        // NOTE TO SELF: IGNORE some stuff
        vvi edgepolys(e);
        vector<ll> areas(npoly);
        vi source(npoly), sink(npoly);
        rep(i, 0, npoly){
            vector<P> pp;
            for(int pid : polypoints[i]){
                pp.pb(points[pid]);
            }
            areas[i] = polygonArea2(pp);
            if(areas[i] < 0) continue;
            d.addEdge(i * 2, i * 2 + 1, areas[i]);
            // cout << "poly " << i << endl;
            for(int eid : polyedges[i]){
        //         cout << eid << " " << points[epid[eid][0]] << " to " << points[epid[eid][1]] << endl;
                edgepolys[eid].pb(i);
            }
        }
        rep(i, 0, e){
            if(et[i] == "W") continue;
            if(et[i] == "E"){
                for(int p : edgepolys[i]) {
                    source[p] = true;
                    d.addEdge(supersource, 2 * p, 1e9);
                }
                continue;
            }
            if(et[i] == "X"){
                for(int p : edgepolys[i]) {
                    sink[p] = true;
                    d.addEdge(2 * p + 1, supersink, 1e9);
                }
                continue;
            }
            for(int p1 : edgepolys[i]){
                for(int p2 : edgepolys[i]) {
                    if(p1 == p2) continue;
                    d.addEdge(2 * p1 + 1, 2 * p2, 1e9);
                }
            }
        }
        ll mf = d.calc(supersource, supersink);
        cout << fixed << setprecision(1) << ld(mf)/2 << "\n";
    }

    return 0;
}
