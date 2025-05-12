#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

ll solve(ll l, ll m, ll r, vector<pair<ll, ll>> ques) {
    ranges::sort(ques);
    
    vector<pair<ll, ll>> comp;
    for (int i = 0; i < sz(ques); i++) {
        ll s = ques[i].first;
        ll t = ques[i].second;
        while (i+1 < sz(ques) && ques[i+1].first <= t) {
            t = max(t, ques[i+1].second);
            i++;
        }
        comp.push_back({s, t});
    }


    ll tot2 = 0;
    for (auto [s, t] : comp) tot2 += 2*(t-s);

    ll res = 1e18;
    ll best = tot2;
    for (int i = sz(comp)-1; i >= 0; i--) {
        auto [s, t] = comp[i];

        res = min(res, (max(m, t) - l) + max(0ll, t - m) + (r - l) + (best - tot2));

        tot2 -= 2*(t - s);
        best = min(best, (r - s) + tot2);
    }
    res = min(res, (m - l) + (r - l) + best);

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    ll h0;
    cin >> h0;

    vector<pair<ll, ll>> ltor, rtol;
    ll lo = h0, hi = h0;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        if (x < y) ltor.push_back({-y, -x});
        else rtol.push_back({y, x});
        lo = min({lo, x, y});
        hi = max({hi, x, y});
    }

    ll res = min(solve(lo, h0, hi, rtol), solve(-hi, -h0, -lo, ltor));
    cout << res << "\n";

    return 0;
}
