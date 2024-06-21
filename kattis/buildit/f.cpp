#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

#define f first
#define s second
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

pii operator+(pii a, pii b) {
    return {a.f + b.f, a.s + b.s};
}
pii operator-(pii a, pii b) {
    return {a.f - b.f, a.s - b.s};
}

vector<pii> dir{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<string> dstr = {"right", "up", "left", "down"};
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    pii cur, dest;
    cin >> cur.f >> cur.s >> dest.f >> dest.s;
    cur = cur - dest;
    set<pii> carts;
    rep(i, 0, n){
        pii a; cin >> a.f >> a.s;
        a = a - dest;
        carts.insert(a);
    }
    auto fix = [&](pii pos, int d, auto &&fix) -> void {
        if(!carts.count(pos)) return;
        carts.erase(pos);
        pos = pos + dir[d];
        fix(pos, d, fix);
        if(pos != pii{0, 0}) carts.insert(pos);
    };
    int moves = 0;
    auto act = [&](int d) -> void {
        cout << dstr[d] << "\n";
        moves++;
        assert(moves <= 100000);
        cur = cur + dir[d];
        fix(cur, d, fix);
    };
    auto go = [&](pii targ, pii avoid, auto &&go) -> void {
        // cout << "go to " << targ.f << "," << targ.s << " from " << cur.f << "," << cur.s << " avoiding " << avoid.f << "," << avoid.s << endl;
        if(targ == cur) return;
        if(targ.f == cur.f && targ.f == avoid.f && min(targ.s, cur.s) <= avoid.s && avoid.s <= max(targ.s, cur.s)) {
            go({targ.f+1, targ.s}, avoid, go);
        }
        else if(targ.s == cur.s && targ.s == avoid.s && min(targ.f, cur.f) <= avoid.f && avoid.f <= max(targ.f, cur.f)) {
            go({targ.f, targ.s+1}, avoid, go);
        }
        targ = targ - cur;
        avoid = avoid - cur;
        int minx = min(targ.f, 0), maxx = max(targ.f, 0), miny = min(targ.s, 0), maxy = max(targ.s, 0);
        if((avoid.s == 0 && (minx <= avoid.f && avoid.f <= maxx)) || (avoid.f == targ.f && (miny <= avoid.s && avoid.s <= maxy))) {
            // go to same y then same x
            rep(i, 0, abs(targ.s)){
                if(targ.s > 0) act(1);
                else act(3);
            }
            rep(i, 0, abs(targ.f)){
                if(targ.f > 0) act(0);
                else act(2);
            }
        } else {
            // go to same x then same y
            rep(i, 0, abs(targ.f)){
                if(targ.f > 0) act(0);
                else act(2);
            }
            rep(i, 0, abs(targ.s)){
                if(targ.s > 0) act(1);
                else act(3);
            }
        }
    };
    while(sz(carts)){
        auto p = *carts.begin();
        auto [x, y] = p;
        // cout << "process " << x << "," << y << "with " << sz(carts) << "left\n";
        if(y != 0){
            go(pii{x, y + (y > 0 ? 1 : -1)}, pii{x, y}, go);
            go(pii{x, (y >  0 ? 1 : -1)}, pii{5000, 5000}, go);
            y = 0;
        }
        if(x != 0) {
            go(pii{x + (x > 0 ? 1 : -1), y}, pii{x, y}, go);
            go(pii{(x > 0 ? 1 : -1), y}, pii{5000, 5000}, go);
        }
    }
    return 0;
}
