#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;
using vl = vector<ll>;

#define sz(x) (int)x.size()

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    for(int cn = 0; cn < nc; cn++){
        ll t; int n; cin >> t >> n;
        ll cur; cin >> cur;
        ll ans = 0;
        for(int i = 1; i < n; i++){
            ll c1; cin >> c1;
            ll forward = c1 > cur ? c1 - cur - 1 : t + c1 - cur - 1;
            ll backward = c1 <= cur ? cur - c1 + 1 : t + cur - c1 + 1;
            ans += min(forward, backward);
            cur = c1;
        }
        cout << ans << "\n";
    }
}
