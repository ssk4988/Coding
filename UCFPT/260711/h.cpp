#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using pii = pair<int,int>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)size(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int p, v; cin >> p >> v;
    map<pii, set<int>> mp;
    rep(i, 0, p) {
        int x, y; cin >> x >> y;
        if(x > y) swap(x, y);
        mp[{x, y}].insert(i);
    }
    vii vase(v);
    rep(i, 0, v) {
        cin >> vase[i].first;
        vase[i].second = i;
    }
    sort(all(vase));
    vi ans(v);
    for(auto [x, idx] : vase) {
        int a = -1;
        if(mp[pii{x, x}].size()) {
            a = *begin(mp[{x, x}]);
            mp[{x, x}].erase(a);
        }else if(mp[{x-1, x}].size()) {
            a = *begin(mp[{x-1, x}]);
            mp[{x-1, x}].erase(a);
        }
        else if(mp[{x, x+1}].size()) {
            a = *begin(mp[{x, x+1}]);
            mp[{x, x+1}].erase(a);
        }
        if(a == -1) {
            cout << "impossible\n";
            return 0;
        }
        else ans[idx] = a;
    }
    rep(i, 0, v) cout << ans[i]+1 << "\n";

    return 0;
}
