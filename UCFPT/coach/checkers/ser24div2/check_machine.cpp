#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
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


/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true iff p lies on the line segment from s to e.
 * Use \texttt{(segDist(s,e,p)<=epsilon)} instead when using Point<double>.
 * Status:
 */

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}



/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-27
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
If a unique intersection point between the line segments going from s1 to e1 and from s2 to e2 exists then it is returned.
If no intersection point exists an empty vector is returned.
If infinitely many exist a vector with 2 elements is returned, containing the endpoints of the common line segment.
The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * Usage:
 * vector<P> inter = segInter(s1,e1,s2,e2);
 * if (sz(inter)==1)
 *   cout << "segments intersect at " << inter[0] << endl;
 * Status: stress-tested, tested on kattis:intersection
 */

template<class P> vector<P> segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b),
	     oc = a.cross(b, c), od = a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
		return {(a * ob - b * oa) / (ob - oa)};
	set<P> s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {all(s)};
}



void WA(string err) {
    cout << "wrong answer " << err << endl;
    exit(0);
}

int main(int argc, char ** argv) {
    string inpf = argv[1];
    string outpf = argv[2];

    ifstream inp(inpf);
    ifstream user(outpf);

    int N;
    inp >> N;

    int answer;
    if (N == 1) answer = 0;
    else if (N == 2) answer = 1;
    else answer = 3*(N-2);

    vector<int> input;
    while (!user.eof()) {
        int x; user >> x;
        input.push_back(x);
        cerr << "read in " << x << endl;
    }

    if (input.size() < 2*N + 1) WA("invalid format");
    int m = input[2*N];
    if (input.size() != 2*N + 1 + 2*m) WA("invalid format");
    if (m != answer) WA("incorrect number of edges");

    vector<Point<ll>> points;
    set<pair<int, int>> pointset;
    for (int i = 0; i < N; i++) {
        int x = input[2*i];
        int y = input[2*i+1];
        if (x < -1e9 || x > 1e9 || y < -1e9 || y > 1e9) WA("point out of range");
        if (pointset.count({x, y})) WA("repeated point");
        points.push_back(Point<ll> (x, y));
        pointset.insert({x, y});
    }

    vector<pair<int, int>> edges;
    set<pair<int, int>> edgeset;
    for (int i = 0; i < m; i++) {
        int u = input[2*N + 1 + 2*i];
        int v = input[2*N + 1 + 2*i+1];
        if (u < 1 || u > N || v < 1 || v > N || u == v) WA("invalid edge format");
        u--; v--;
        if (edgeset.count({u, v})) WA("repeated edge");
        edges.push_back({u, v});
        edgeset.insert({u, v});
    }

    for (int a = 0; a < m; a++) {
        for (int b = 0; b < m; b++) {
            if (a == b) continue;

            Point<ll> s1 = points[edges[a].first];
            Point<ll> e1 = points[edges[a].second];
            Point<ll> s2 = points[edges[b].first];
            Point<ll> e2 = points[edges[b].second];
            vector<Point<ll>> inter = segInter(s1, e1, s2, e2);
            if (edges[a].first == edges[b].first || edges[a].first == edges[b].second || 
                edges[a].second == edges[b].first || edges[a].second == edges[b].second) {
                if (inter.size() == 2) WA("edges intersect");
            }
            else {
                if (inter.size() > 0) WA("edges intersect");
            }
        }
    }

    return 0;
}
