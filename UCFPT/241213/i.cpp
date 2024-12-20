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
#define sz(x) (int) x.size()

void solve() {
    int n; ll S, M; cin >> n >> S >> M;
    vector<ll> a(n);
    rep(i, 0, n) cin >> a[i];
    vector<ll> factors;
    for(ll d = 1; d*d <= M; d++) {
        if(M % d == 0) {
            factors.push_back(d);
            if(d*d != M)
                factors.push_back(M/d);
        }
    }
    sort(all(factors));

    auto get_idx = [&](ll x) -> int {
        auto it = lower_bound(all(factors), x);
        return it - begin(factors);
    };

    int k = sz(factors);
    vector<vii> splits(k);
    rep(i, 0, k) rep(j, 0, k) {
        int idx = get_idx(factors[i]*factors[j]);
        if(idx == sz(factors)) continue;
        if(factors[idx] == factors[i]*factors[j])
            splits[idx].emplace_back(i, j);
    }

    vi frq(k);
    rep(i, 0, n) {
        int idx = get_idx(a[i]);
        if(idx == k) continue;
        if(factors[idx] == a[i])
            frq[idx]++;
    }

    ll res = 2e18;
    auto backtrack = [&](int cur, int prv, int f, ll sum, ll cost, auto &backtrack) {
        if(cur == 0) {
            if(sum > S) return;
            cost += abs((S-sum)-frq[0]) - frq[0];
            res = min(res, cost);
            return;
        }

        for(auto [j, i]: splits[cur]) if(i != 0) {
            if(prv < j) continue;
            int new_f = 1;
            if(j == prv) new_f += f;
            int new_cost = cost + (new_f <= frq[j] ? -1 : 1);
            backtrack(i, j, new_f, sum + factors[j], new_cost, backtrack);
        }
    };
    backtrack(k-1, k-1, 0, 0, n, backtrack);
    if(res == 2e18) {
        cout << -1 << '\n';
        return;
    }
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    // int t; cin >> t;
    solve();

    return 0;
}
