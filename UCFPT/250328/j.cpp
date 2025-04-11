#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

random_device rdev;
mt19937 rng(rdev());

using ld = long double;

template<class T>
struct Point {
    typedef Point P;
    T x=0, y=0;
    Point(T x=0, T y=0) : x(x), y(y) {}
    Point operator+(P p) const { return Point(x+p.x, y+p.y); }
    Point operator-(P p) const { return Point(x-p.x, y-p.y); }
    Point operator*(T d) const { return Point(x*d, y*d); }
    Point operator/(T d) const { return Point(x/d, y/d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x+y*y; }
    ld dist() { return sqrtl(dist2()); }
    P rotate(ld a) const {
        return P(x*cosl(a)-y*sinl(a),x*sinl(a)+y*cosl(a));
    }
    ld angle() const {
        return atan2l(y, x);
    }
};
const ld eps = 1e-11;
using P = Point<ld>;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<vector<P>> pieces(n);
    vector<tuple<ld, int, int>> sides;
    rep(i, 0, n) {
        int k; cin >> k;
        pieces[i].resize(k);
        rep(j, 0, k){
            cin >> pieces[i][j].x >> pieces[i][j].y;
        }
        rep(j, 0, k) {
            P p = pieces[i][j], q = pieces[i][(j+1)%k];
            sides.emplace_back((p-q).dist(), i, j);
        }
    }
    sort(all(sides));
    vector<vector<array<int, 3>>> adj(n);
    rep(i, 0, sz(sides)-1){
        auto [d1, i1, j1] = sides[i];
        auto [d2, i2, j2] = sides[i+1];
        if(abs(d2-d1)>eps) continue;
        if(abs(1-d1)<eps) continue;
        adj[i1].push_back({i2, j1, j2});
        adj[i2].push_back({i1, j2, j1});
    }
    queue<int> q;
    vi seen(n);
    rep(i, 0, n) {
        bool found = false;
        rep(cur, 0, sz(pieces[i])) {
            int prv = (cur + sz(pieces[i])-1)%sz(pieces[i]);
            int nxt = (cur+1)%sz(pieces[i]);
            if(abs((pieces[i][prv]-pieces[i][cur]).dot(pieces[i][nxt]-pieces[i][cur])) < eps){
                found = true;
                P ref = pieces[i][cur];
                for(auto &p : pieces[i]) {
                    p = p - ref;
                }
                ld angle = pieces[i][nxt].angle();
                for(auto &p : pieces[i]) {
                    p = p.rotate(-angle);
                }
                break;
            }
        }
        if(found) {
            q.push(i);
            break;
        }
    }
    if(sz(q) == 0) {
        assert(false);
    }
    while(sz(q)) {
        int u = q.front(); q.pop();
        if(seen[u]) continue;
        seen[u] = true;
        for(auto [v, s1, s2] : adj[u]) {
            q.push(v);
            int s12 = (s1+1)%sz(pieces[u]), s22 = (s2+1)%sz(pieces[v]);
            P d = pieces[v][s22] - pieces[u][s1];
            for(auto &p : pieces[v]) p = p - d;
            P side1 = pieces[u][s12]-pieces[u][s1], side2 = pieces[v][s22] - pieces[v][s2];
            ld angle1 = side1.angle(), angle2 = side2.angle();
            angle1 += acosl(-1);
            ld displacement = angle1 - angle2;
            P ref = pieces[v][s22];
            for(auto &p : pieces[v]) {
                p = ref + (p - ref).rotate(displacement);
            }
        }
    }
    rep(i, 0, n) assert(seen[i]);
    rep(i, 0, n) {
        rep(j, 0, sz(pieces[i])) {
            for(auto d : {pieces[i][j].x, pieces[i][j].y}) {
                ld v = clamp(d, ld(0), ld(1));
                cout << fixed << setprecision(12) << v << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }


    return 0;
}
