#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using int128 = __int128_t;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int w, h, l; cin >> w >> h >> l;
        int128 v = int128(w) * int128(h) * int128(l);
        int n; cin >> n;
        map<int, vector<array<int, 4>>> events;
        int128 v1 = 0;
        rep(i, 0, n){
            int xl, yl, zl, xr, yr, zr; cin >> xl >> yl >> zl >> xr >> yr >> zr;
            v1 += int128(xr - xl) * int128(yr - yl) * int128(zr - zl);
            events[xl].push_back({yl, yr, zl, zr});
            events[xr].push_back({yl, yr, zl, zr});
        }
        set<pii> s;
        set<pii> target{{0, 0}, {h, 0}, {0, l}, {h, l}};
        bool works = v1 == v;
        for(auto &[key, val] : events){
            for(auto rect : val){
                rep(i, 0, 2){
                    rep(j, 2, 4){
                        pii p = {rect[i], rect[j]};
                        if(s.count(p)) s.erase(p);
                        else s.insert(p);
                    }
                }
            }
            if(s != target && key != w) works = false;
        }
        cout << (works ? "Yes" : "No") << "\n";
    }

    return 0;
}
