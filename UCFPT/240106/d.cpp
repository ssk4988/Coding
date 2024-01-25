#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int x, y; cin >> x >> y;
    int n; cin >> n;
    vii p(n);
    ll dist = 0;
    map<ll, ll> upper, lower, highest;
    rep(i, 0, n){
        cin >> p[i].second >> p[i].first;
        lower[p[i].second]++;
        highest[p[i].second] = max(highest[p[i].second], ll(p[i].first));
    }
    for(auto [h, w] : highest){
        dist += 2 * w;
    }
    sort(all(p));
    ll preh = 0;
    ll ans = LLONG_MAX;
    for(auto [h, w] : p){
        ll dh = h - preh;
        dist -= 2 * sz(lower) * dh;
        dist += 2 * sz(upper) * dh;
        // lower--, upper++;
        lower[w]--;
        if(lower[w] == 0) lower.erase(w);
        upper[w]++;
        ans = min(ans, dist);
        // cout << h << " " << dist << "\n";
        preh = h;
    }
    ans += x - 1;
    cout << ans << "\n";

    return 0;
}
