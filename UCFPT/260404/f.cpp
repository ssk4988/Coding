#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

using int128 = __int128_t;

string tostr(int128 x) {
    string s;
    if(x == 0) s += '0';
    while(x) {
        s += '0' + (x % 10);
        x /= 10;
    }
    reverse(all(s));
    return s;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int tp; cin >> tp;
        ll qt, qidx; cin >> qidx >> qt;
        if(qt == 0) {
            cout << 0 << "\n";
            continue;
        }
        if(qt <= qidx * 2 - 1) {
            cout << qidx << "\n";
            continue;
        }
        if(tp == 1) {
            int128 idx = qidx;
            int128 t = 2 * idx - 1;
            while(idx + t < qt) {
                t = t + idx + 1;
                idx = t / 2;
            }
            idx -= qt - t;
            cout << tostr(idx) << "\n";
        } else {
            int128 idx = qidx;
            int128 t = qt;
            t += idx;
            idx = 0;
            t++;
            idx = t / 2;
            while(t != 2 * idx - 1) {
                // cerr << "t: " << tostr(t) << " idx: " << tostr(idx) << endl;
                idx = t/3;
                t = t - 1 - t/3;
            }
            cout << tostr(idx) << "\n";
        }
    }

    return 0;
}
