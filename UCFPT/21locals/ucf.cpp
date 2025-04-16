#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

const ll mod = 1000000007, LIM = 1500000;
ll *inv = new ll[LIM] - 1;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    inv[1] = 1;
    vl fact(LIM), ifact(LIM);
    fact[0] = ifact[0] = 1;
    rep(i,2,LIM) inv[i] = mod-(mod / i) * inv[mod % i] % mod;
    rep(i, 1, LIM) {
        fact[i] = fact[i-1] * i % mod;
        ifact[i] = ifact[i-1] * inv[i] % mod;
    }
    auto C = [&](ll n, ll k) -> ll {
        if(n < 0 || k > n) return 0;
        return fact[n] * ifact[k] % mod * ifact[n-k] % mod;
    };
    int n; cin >> n;
    vii p(n);
    rep(i, 0, n) {
        cin >> p[i].first >> p[i].second;
    }
    int q; cin >> q;
    rep(i, 0, q) {
        vii cs(2);
        rep(j, 0, 2) {
            cin >> cs[j].first >> cs[j].second;
        }
        sort(all(cs));
        bool horiz = cs[0].second > cs[1].second;
        int ly = min(cs[0].second, cs[1].second);
        int uy = max(cs[0].second, cs[1].second);
        for(auto [x, y] : p) {
            if(cs[0].first <= x && x <= cs[1].first && ly <= y && y <= uy) {
                cs.push_back({x, y});
            }
        }
        if(horiz) {
            for(auto &[x, y] : cs) {
                y = abs(y - uy);
            }
        }
        sort(all(cs));
        // for(auto [x, y] : cs) {
        //     cout << x << "," << y << endl;
        // }
        vl dp(sz(cs));
        rep(i, 0, sz(cs)) {
            auto [x, y] = cs[0];
            auto [x1, y1] = cs[i];
            dp[i] = C(x1-x + y1-y, x1-x);
        }
        rep(i, 1, sz(cs)) {

            rep(j, i+1, sz(cs)) {
                auto [x, y] = cs[i];
                auto [x1, y1] = cs[j];
                if(x > x1 || y > y1) continue;
                ll ways = C(x1-x + y1-y, x1-x);
                (dp[j] -= ways * dp[i]) %= mod;
                (dp[j] += mod) %= mod;
            }
        }
        cout << dp.back() << "\n";
    }
    return 0;
}