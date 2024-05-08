#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ld = long double;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct Line {
    mutable ld k, m, p;
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(ld x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
    const ld inf = (1/0.0L);
    ld div(ld a, ld b) {
        return a / b;
    }
    bool isect(iterator x, iterator y) {
        if(y == end()) return x->p = inf, 0;
        if(x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ld k, ld m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if(x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ld query(ld x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
const ld inf = (1/0.0L);
int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vi x(n), y(n), vx(n), vy(n);
    rep(i, 0, n) cin >> x[i] >> y[i] >> vx[i] >> vy[i];
    array<LineContainer, 4> lcs;
    LineContainer &x_min = lcs[0], &x_max = lcs[1], &y_min = lcs[2], &y_max = lcs[3];
    rep(i, 0, n) {
        x_max.add(vx[i], x[i]);
        x_min.add(-vx[i], -x[i]);
        y_max.add(vy[i], y[i]);
        y_min.add(-vy[i], -y[i]);
    }

    auto calc = [&](ld t) -> ld {
        return (x_max.query(t) + x_min.query(t)) * (y_max.query(t) + y_min.query(t));
    };
    vector<decltype(x_min.begin())> lc_it;
    rep(i, 0, 4) lc_it.push_back(lcs[i].begin());
    ld pre_p = 0;
    ld ans = calc(0);
    while(true){
        if(pre_p > 0) ans = min(ans, calc(pre_p));
        ld a = lc_it[1]->k + lc_it[0]->k;
        ld b = lc_it[1]->m + lc_it[0]->m;
        ld c = lc_it[3]->k + lc_it[2]->k;
        ld d = lc_it[3]->m + lc_it[2]->m;
        if(a * c != 0){
            ld mid = -(b * c + a * d) / (2 * a * c);
            if(mid > 0) ans = min(ans, calc(mid));
        }

        ld nex_p = inf;
        int source = -1;
        rep(i, 0, 4){
            if(lc_it[i]->p != inf && lc_it[i]->p < nex_p){
                source = i;
                nex_p = lc_it[i]->p;
            }
        }
        if(source == -1) {
            break;
        }
        lc_it[source] = next(lc_it[source]);
        pre_p = nex_p;
    }


    cout << setprecision(12) << fixed << ans << '\n';

    return 0;
}
