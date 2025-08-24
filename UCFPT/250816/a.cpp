#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi a(k);
    rep(i, 0, k) cin >> a[i];
    k = *min_element(all(a));
    vector<tuple<int, string, int>> events;
    rep(i, 0, n) {
        int c; string s; cin >> c >> s;
        events.emplace_back(c, s, i);
    }
    sort(all(events));
    reverse(all(events));
    map<string, int> seen;
    vi ans(n);
    int tot = 0;
    for(auto [w, t, i] : events) {
        ans[i] = tot - seen[t] + min(k-1, seen[t]) + 1;
        tot -= seen[t];
        seen[t] = min(k, seen[t]+1);
        tot += seen[t];
    }
    rep(i, 0, n) {
        cout << ans[i] << "\n";
    }

    return 0;
}
