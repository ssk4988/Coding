#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

struct FT {
    vector<ll> s;
    FT(int n): s(n) {}
    void update(int pos, ll dif) {
        for(; pos < sz(s); pos |= pos + 1) s[pos] += dif;
    }
    ll query(int pos) {
        ll res = 0;
        for(; pos > 0; pos &= pos - 1) res += s[pos-1];
        return res;
    }
};

struct FT2 {
    vector<vi> ys; vector<FT> ft;
    FT2(int limx): ys(limx) {}
    void fakeUpdate(int x, int y) {
        for(; x < sz(ys); x |= x+1) ys[x].push_back(y);
    }
    void init() {
        for(vi &v: ys) sort(all(v)), ft.emplace_back(sz(v));
    }
    int ind(int x, int y) {
        return (int)(lower_bound(all(ys[x]), y) - ys[x].begin());
    }
    void update(int x, int y, ll dif) {
        for(; x < sz(ys); x |= x+1)
            ft[x].update(ind(x, y), dif);
    }
    ll query(int x, int y) {
        ll sum = 0;
        for(; x; x &= x-1)
            sum += ft[x-1].query(ind(x-1, y));
        return sum;
    }
};
 
using query = tuple<int, int, int, int, int>;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int q; cin >> q;
    vector<query> queries(q);

    vi xs, ys;
    for(auto &[t, x1, y1, x2, y2]: queries) {
        cin >> t >> x1 >> y1;
        xs.push_back(x1); ys.push_back(y1);
        if(t == 2) {
            cin >> x2 >> y2;
            xs.push_back(x2), ys.push_back(y2);
        }
    }

    sort(all(xs)); sort(all(ys));
    xs.erase(unique(all(xs)), xs.end());
    ys.erase(unique(all(ys)), ys.end());

    map<int, int> xCC, yCC;
    rep(i, 0, sz(xs)) xCC[xs[i]] = i+1;
    rep(i, 0, sz(ys)) yCC[ys[i]] = i+1;

    FT2 rects(sz(xs) + 1), pts(sz(xs) + 2);

    for(auto &[t, x1, y1, x2, y2]: queries) {
        x1 = xCC[x1], y1 = yCC[y1];
        if(t == 1) {
            rects.fakeUpdate(x1, y1);
        }
        else {
            x2 = xCC[x2], y2 = yCC[y2];
            pts.fakeUpdate(x2, y2);
            pts.fakeUpdate(x2, y1-1);
            pts.fakeUpdate(x1-1, y2);
            pts.fakeUpdate(x1-1, y1-1);
        }
    }

    rects.init(); pts.init();

    ll cnt = 0;
    for(auto &[t, x1, y1, x2, y2]: queries) {
        if(t == 1) {
            cnt += pts.query(x1, y1);
            cout << cnt << '\n';
            rects.update(x1, y1, 1);
        }
        else {
            cnt += rects.query(x2+1, y2+1);
            cnt -= rects.query(x1, y2+1);
            cnt -= rects.query(x2+1, y1);
            cnt += rects.query(x1, y1);
            cout << cnt << '\n';

            pts.update(x2, y2, 1);
            pts.update(x2, y1-1, -1);
            pts.update(x1-1, y2, -1);
            pts.update(x1-1, y1-1, 1);
        }
    }

    return 0;
}