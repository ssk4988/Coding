#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

struct pt {
    double x, y;
    pt(double x = 0, double y = 0): x(x), y(y) {}
    bool operator<(pt p) { return tie(x,p.x) < tie(y,p.y); }
    bool operator==(pt p) {return tie(x,p.x) == tie(y,p.y); }
    pt operator-(pt p) { return pt(x-p.x, y-p.y);}
    double cross(pt p) { return x * p.y - y * p.x; }
    double cross(pt p, pt q) { return (p - *this).cross(q - *this); }
};

double T = 1e20;

template<class P> vector<P> convex_hull(vector<P> pts) {
    sort(all(pts));
    vector<P> hull(sz(pts)+1);
    int k = 0, t = 2;
    rep(_, 0, 2) {
        for(P p : pts) {
            while(k >= t && hull[k-2].cross(hull[k-1], p) <= 0) k--;
            hull[k++] = p;
        }
        reverse(all(pts));
        t=k+1;
    }
    hull.resize(k-1);
    return hull;
}

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vvi grid(n, vi(n));
    rep(i, 0, n) rep(j, 0, n)
        cin >> grid[i][j];
    
    int bound = (2*n+1) * n;
    int cent = n*n;

    vector<pt> pts;

    rep(r, cent, cent+n) rep(c, cent, cent+n) {
        vvi dist(bound, vi(bound, 1e9));
        dist[r][c] = 0;
        using a3 = array<int, 3>;
        priority_queue<a3, vector<a3>, greater<>> pq;
        pq.push({0, r, c});
        while(!pq.empty()) {
            auto [d, cr, cc] = pq.top(); pq.pop();
            if(d > dist[cr][cc]) continue;

            if(cr != r && cc != c && abs(cr-r)%n == 0 && abs(cc-c)%n == 0) {
                int i = (cr-r)/n, j = (cc-c)/n;
                if(abs(i) + abs(j) <= n)
                    pts.emplace_back(i / (double) d, j / (double) d);
            }

            if(abs(cr-r)/n + abs(cc-c)/n > n+1) continue;

            rep(k, 0, 4) {
                int nr = cr + dr[k], nc = cc + dc[k];
                if(nr < 0 || nr >= bound || nc < 0 || nc >= bound)
                    continue;
                int wt = abs(grid[cr%n][cc%n] - grid[nr%n][nc%n]) + 1;
                if(d + wt >= dist[nr][nc]) continue;
                dist[nr][nc] = d + wt;
                pq.push({d+wt, nr, nc});
            }
        }
    }

    sort(all(pts));
    pts.erase(unique(all(pts)), end(pts));

    for(auto [x, y]: pts) cout << x << ' ' << y << endl;
    pts = convex_hull(pts);

    double area = 0;
    int k = sz(pts);
    rep(i, 0, k)
        area += pts[i].cross(pts[(i+1)%k]);
    area /= 2;

    cout << setprecision(10) << area * T * T << '\n';

    return 0;
}
