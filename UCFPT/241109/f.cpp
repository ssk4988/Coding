#include <bits/stdc++.h>

using namespace std;

using vi =vector<int>;
using ll = long long;
using vvi = vector<vi>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) x.size()

#define x first
#define y second

ll cross(pll a, pll b) {
    return a.x * b.y - a.y * b.x;
}

pll operator-(pll a, pll b) {
    return {a.x - b.x, a.y - b.y};
}

pll operator+(pll a, pll b) {
    return {a.x + b.x, a.y + b.y};
}

int sgn(pll a){
    return a.y > 0 || (a.y == 0 && a.x > 0);
}

bool cmp(const pll &a, const pll &b) {
    if(sgn(a) != sgn(b)) return sgn(a) < sgn(b);
    return cross(a, b) > 0;
}

void printpll(pll a){
    cout << a.x << "/" << 2 << " ";
    cout << a.y << "/" << 2;
    cout << " ";
}



#define sgn(x) (x > 0) - (x < 0)

void solve() {
    int n; cin >> n;
    vll p(n);
    ll minx = LLONG_MAX, miny = LLONG_MAX, maxx = LLONG_MIN, maxy = LLONG_MIN;
    rep(i, 0, n) {
        cin >> p[i].x >> p[i].y;
        p[i].x *= 2;
        p[i].y *= 2;
        minx = min(minx, p[i].x);
        miny = min(miny, p[i].y);
        maxx = max(maxx, p[i].x);
        maxy = max(maxy, p[i].y);
    }
    ll cx = (minx + maxx) / 2;
    ll cy = (miny + maxy) / 2;
    rep(i, 0, n){
        p[i].x -= cx;
        p[i].y -= cy;
    }
    vector<pair<pll, int>> events;
    int cover = 0;
    set<pll, decltype(cmp)*> concaves(cmp);
    map<pll, int, decltype(cmp)*> exits(cmp);
    rep(i, 0, n){
        int j = (i+1) % n;
        int h = (i+n-1) % n;
        pll a = p[i], b = p[j];
        events.emplace_back(a, 0);
        events.emplace_back(b, 0);
        if(cross(a, b) == 0) continue;
        if (cross(p[j] - p[i], p[h] - p[i]) < 0) concaves.insert(p[i]);
        if(cross(a, b) < 0) swap(a, b);
        if(cmp(b, a)) cover++;
        events.emplace_back(a, 1);
        events.emplace_back(b, -1);
    }
    auto p2(p);
    sort(all(p2), cmp);
    for (int i = 0; i < n; i++) {
        pll a = p2[i], b = p2[(i+1)%n];
        if (cross(a, b) == 0) continue;
        events.emplace_back(pll{(a.x+b.x)/2, (a.y+b.y)/2}, 0);
    }
    sort(all(events), [](auto a, auto b) -> bool {
        if(cmp(a.first, b.first)) return true;
        if(cmp(b.first, a.first)) return false;
        return a.second < b.second;
    });
    vector<pair<pll, int>> evs;
    for(auto [point, add] : events) {
        if(sz(evs) == 0 || !(sgn(add) == sgn(evs.back().second) && !cmp(evs.back().first, point) && !cmp(point, evs.back().first))){
            evs.emplace_back(point, add);
        } else evs.back().second += add;
    }
    set<pll> cands;
    set<pll, decltype(cmp)*> ignores(cmp);
    vi works;
    for(auto [p, t] : evs) {
        if(abs(t) >= 2 && concaves.count(p)){
            ignores.insert(p);
        } 
        if (t == 0 && cover <= 1) cands.insert(p);
        cover += t;
    }
    for(pll inter : cands){
        if(!ignores.count(inter)) {
            inter.x += cx, inter.y += cy;
            printpll(pll(cx, cy));
            printpll(inter);
            cout << "\n";
            return;
        }
    }
    cout << "impossible\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    solve();

    return 0;
}
