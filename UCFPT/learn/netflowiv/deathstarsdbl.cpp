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

struct Dinic
{
    struct Edge
    {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc - c, 0LL); } // if you need flows
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, ll rcap = 0)
    {
        // cout << "added " << a << " connection to " << b << nL;
        adj[a].push_back({b, sz(adj[b]), c, c});
        adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
    }
    ll dfs(int v, int t, ll f)
    {
        if (v == t || !f)
            return f;
        for (int &i = ptr[v]; i < sz(adj[v]); i++)
        {
            Edge &e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (ll p = dfs(e.to, t, min(f, e.c)))
                {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    ll calc(int s, int t)
    {
        ll flow = 0;
        q[0] = s;
        rep(L, 0, 31) do
        { // 'int L=30' maybe faster for random data
            lvl = ptr = vi(sz(q));
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t])
            {
                int v = q[qi++];
                for (Edge e : adj[v])
                    if (!lvl[e.to] && e.c >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while (ll p = dfs(s, t, LLONG_MAX))
                flow += p;
        }
        while (lvl[t])
            ;
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
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
vector<P> circleLine(P c, double r, P a, P b) {
	P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
	double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
	if (h2 < 0) return {};
	if (h2 == 0) return {p};
	P h = ab.unit() * sqrt(h2);
	return {p - h, p + h};
}


using P = Point<ld>;
ld eps = 1e-8;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n;
    vector<P> stars(n);
    rep(i, 0, n){
        cin >> stars[i].x >> stars[i].y;
    }
    cin >> m;
    vector<P> ships(m), shipe(m);
    vd speed(m), range(m), energy(m);
    rep(i, 0, m) {
        cin >> ships[i].x >> ships[i].y >> shipe[i].x >> shipe[i].y >> speed[i] >> range[i] >> energy[i];
    }
    Dinic d(100000);
    int source = n, sink = n+1;
    int nxt_id = n+2;
    rep(i, 0, m){
        d.addEdge(source, i, energy[i] * 1e5);
    }
    rep(i, 0, n){
        vector<pair<ld, int>> events;
        rep(j, 0, m) {
            auto inters = circleLine(stars[i], range[i], ships[j], shipe[j]);
            P dir = (shipe[j] - ships[j]).unit();
            if(sz(inters) < 2) continue;
            if(dir.dot(inters[0] - ships[j]) > dir.dot(inters[1] - ships[j])) swap(inters[0], inters[1]);
            ld lo = max(0.L, dir.dot(inters[0] - ships[j]) / speed[j]);
            ld hi = min((shipe[j] - ships[j]).dist() / speed[j], dir.dot(inters[1] - ships[j]) / speed[j]);
            if(lo + eps > hi) continue;
            cout << i << " " << j << " " << lo << " " << hi << "\n";
            events.emplace_back(lo, j);
            events.emplace_back(hi, j);
        }
        if(sz(events) == 0) continue;
        sort(all(events));
        int mask = 0;
        ld prevtime = events[0].f;
        for(auto [time, ship] : events){
            mask ^= 1 << ship;
            ld t = time - prevtime;
            if(t > eps) {
                rep(shipid, 0, m) {
                    if((mask >> shipid) & 1) {
                        d.addEdge(shipid, nxt_id, 1e9 * 1e5);
                    }
                }
                // cout << nxt_id << " " << t << endl;
                d.addEdge(nxt_id++, sink, t * 1e5);
            }
            prevtime = time;
        }
    }
    ll mf = d.calc(source, sink);
    cout << fixed << setprecision(4) << mf/1e5 << "\n";
    
    return 0;
}
