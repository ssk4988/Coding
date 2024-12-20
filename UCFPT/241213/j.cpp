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

const ll inf = 1e16;
void solve() {
    int n, m; cin >> n >> m;
    vl a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    vl c(a);
    vl x(m), t(m);
    vi p(n);
    vector<vl> chargers(n);
    rep(i, 0, m){
        cin >> x[i] >> t[i]; t[i]--;
        chargers[t[i]].push_back(x[i]);
    }
    rep(i, 0, n){
        chargers[i].push_back(inf+1);
    }
    auto cmp = [&](int i, int j) -> bool {
        return pair<ll, int>{chargers[i][p[i]], i} < pair<ll, int>{chargers[j][p[j]], j};
    };
    set<int, decltype(cmp)> pq(cmp);
    x.push_back(inf);
    rep(i, 0, n){
        pq.insert(i);
    }
    ll ans = 0;
    ll prv = 0;
    // cout << sz(x) << " " << sz(t) << endl;
    rep(i, 0, sz(x)){
        ll dx = x[i] - prv;
        // cout << x[i] << " " << dx << endl;
        while(sz(pq) && dx) {
            int y = *begin(pq);
            pq.erase(y);
            ll amt = min(c[y], dx);
            // cout << "use " << y << " for " << amt << " on range " << x[i]-dx << " to " << x[i]-dx+amt << endl;
            ans += amt;
            c[y] -= amt;
            dx -= amt;
            if(c[y]) pq.insert(y);
        }
        // cout << dx << " leftover "  << endl;
        prv = x[i];
        if(i + 1 < sz(x)){
            int y = t[i];
            if(pq.count(y)){
                pq.erase(y);
            }
            c[y] = a[y];
            p[y]++;
            pq.insert(y);
            // cout << "reinsert " << y << endl;
        }
        if(dx) break;
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
