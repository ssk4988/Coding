#include <bits/stdc++.h>
using namespace std;


using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

const int p16 = 1 << 16;
const ll p32 = 1LL << 32;
ll encode(pii p) {
    return ll(p16) * p.first + p.second;
}
pii decode(ll v) {
    return pii{v / p16, v % p16};
}
ll transf(ll x, ll y, int q) {
    if(y >= 0) {
        x ^= x << y;
    } else x ^= x >> -y;
    return (x + q) & (p32-1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        int xd, yd; cin >> xd >> yd;
        vector<pii> pts;
        ll last_gen = 0;
        rep(i, 0, k) {
            int p, q; cin >> p >> q;
            if(p >= 0) {
                pts.push_back({p, q});
                continue;
            }
            p = abs(p);
            rep(_, 0, p) {
                last_gen = (transf(transf(transf(transf(last_gen, 16, q), -11, q), 20, q), -24, q) * 161120241) & (p32-1);
                pts.push_back(decode(last_gen));
            }
        }
        for(auto [x, y] : pts) {
            cerr << x << " " << y << endl;
        }
    }
    
    return 0;
}
