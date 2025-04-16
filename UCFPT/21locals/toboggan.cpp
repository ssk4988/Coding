#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vii = vector<pii>;
using ld = double; 

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ld L; int n; ld lim; cin >> L >> n >> lim;
    vector<ld> boosts(n);
    rep(i, 0, n) cin >> boosts[i];
    sort(all(boosts));
    assert(boosts[0] == 0);
    assert(boosts.back() < L);
    boosts.push_back(L);

    auto test = [&](ld jump) -> bool {
        ld pos = 0;
        ld v = jump;
        ld t = 0;
        rep(i, 1, sz(boosts)) {
            ld diff = boosts[i] - pos;
            if(v * v / 2 < diff) return false;
            ld reach = v - sqrtl(max(ld(0), v * v - 2 * diff));
            pos += diff;
            t += reach;
            v += jump - reach;
        }
        return t <= lim;
    };
    ld lo = 0, hi = 2e9;
    assert(test(hi));
    rep(iter, 0, 300) {
        ld mid = (lo + hi) / 2;
        if(test(mid)) hi = mid;
        else lo = mid;
    }
    cout << fixed << setprecision(10) << lo << endl;

    return 0;
}