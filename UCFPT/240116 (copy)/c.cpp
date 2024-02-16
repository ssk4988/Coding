#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int v; cin >> v;
    vl divs;
    rep(i, 1, v + 1){
        if(v % i == 0) divs.push_back(i);
    }
    ll ans = 1e15;
    auto bt = [&](int idx, int used, ll prod, vl &path, auto &&bt) -> void {
        if(v % prod != 0) return;
        if(used == 2){
            ll last = v / prod;
            ans = min(ans, 2 * (path[0] * path[1] + (path[0] + path[1]) * last));
            return;
        }
        rep(i, idx, sz(divs)){
            path.push_back(divs[i]);
            bt(i, used+1, prod * divs[i], path, bt);
            path.pop_back();
        }
    };
    vl path;
    // if(v == 1){
    //     cout << 6 << "\n";
    //     return 0;
    // }
    bt(0, 0, 1, path, bt);
    cout << ans << "\n";
    return 0;
}