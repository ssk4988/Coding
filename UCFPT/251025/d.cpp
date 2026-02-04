#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

template<class T>
struct Point {
    T x=0, y=0;
    using P = Point<T>;
    Point(T x, T y):x(x),y(y){}
    P operator+(P p) const { return P(x+p.x,y+p.y); }
    P operator-(P p) const { return P(x-p.x,y-p.y); }
    P operator*(T p) const { return P(x*p,y*p); }
    P operator/(T p) const { return P(x/p,y/p); }
    T dot(P p) const { return x*p.x+y*p.y; }
    T dist2() const { return x*x+y*y; }
    T cross(P p) const { return x*p.y-y*p.x; }
    T cross(P p, P q) const { return (p-*this).cross(q-*this); }
    bool operator<(P p) const { return pair{x,y} < pair{p.x,p.y}; }
    bool operator==(P p) const { return pair{x,y} == pair{p.x,p.y}; }
};

template<class P> 
vector<P> convex_hull(vector<P> pts) {
    if(sz(pts) == 1) return pts;
    stable_sort(all(pts));
    vector<P> hull(sz(pts)+1);
    int k = 0, t = 2;
    rep(_, 0, 2) {
        for(P p : pts) {
            while(k >= t && hull[k-2].cross(hull[k-1],p) <= 0) k--;
            hull[k++] = p;
        }
        reverse(all(pts));
        t=k+1;
    }
    hull.resize(k-1);
    return hull;
}

using P = Point<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<P> pts(n);
    rep(i, 0 ,n) {
        cin >> pts[i].x >> pts[i].y;
    }
    sort(all(pts));
    bool line = true;
    rep(i, 0, n) {
        if(pts[0].cross(pts[n-1], pts[i]) != 0) line = false;
    }
    if(line) {
        cout << fixed << setprecision(8) << 
    }

    return 0;
}
