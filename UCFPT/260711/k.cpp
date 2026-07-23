#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pii = pair<int,int>;
using vii = vector<pii>;
using ld = long double;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using P = pair<ld, ld>;
P operator+(P a, P b) {
    return P{a.first + b.first, a.second + b.second};
}
P operator*(P a, ld b) {
    return P{a.first * b, a.second * b};
}
P operator-(P a, P b) {
    return P{a.first - b.first, a.second - b.second};
}
ld dist(P p) {
    return sqrt(p.first * p.first + p.second * p.second);
}
ld dot(P a, P b) {
    return a.first * b.first + a.second * b.second;
}

random_device rd;
mt19937 rng(rd());
const ld eps = 5e-5;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<P> p(n);
    P target;
    cin >> target.first >> target.second;
    rep(i, 0, n) cin >> p[i].first >> p[i].second;
    vector<ld> cur(n);
    rep(i, 0, n) cur[i] = uniform_real_distribution<ld>(0, 1)(rng);
    auto pcalc = [&](vector<ld> &v) {
        ld tot = accumulate(all(v), ld(0));
        P s{0, 0};
        rep(i, 0, n) {
            s = s + p[i] * (v[i] / tot);
        }
        return s;
    };
    auto calc = [&](vector<ld> &v) {
        return dist(pcalc(v) - target);
    };
    ld best_ans = 1e18;
    auto test = [&](vector<ld> &v) {
        auto ans = calc(v);
        if(ans < best_ans) {
            best_ans = ans;
            cur = v;
            // cerr << "improved: " << ans << endl;
            return true;
        }
        return false;
    };
    vi choices(n);
    iota(all(choices), 0);
    int max_iter = 1000000;
    for(ld dif = 10; max_iter > 0 && best_ans > eps; max_iter--, dif /= 1.01) {
        vector<ld> dots(n);
        P pcur = pcalc(cur);
        P dir = target - pcur;
        dir = dir * (1 / dist(dir));
        rep(i, 0, n) {
            P dir1 = p[i] - pcur;
            dir1 = dir1 * pow(1 / dist(dir1), 2);
            dots[i] = dot(dir, dir1);
            dots[i] = max(ld(0), dots[i]);
        }
        ld tot = accumulate(all(dots), ld(0));
        vector<ld> cur2(cur);
        rep(i, 0, n) {
            cur2[i] += dif * dots[i] / tot;
        }
        test(cur2);
    }
    ld tot = accumulate(all(cur), ld(0));
    P s{0, 0};
    rep(i, 0, n) {
        s = s + p[i] * (cur[i] / tot);
        cout << fixed << setprecision(20) << cur[i]/tot << "\n";
    }
    // cerr << fixed << setprecision(20) << best_ans << endl;
    // cerr << s.first << "," << s.second << "\n";

    return 0;
}
