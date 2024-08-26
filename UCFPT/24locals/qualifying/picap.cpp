#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using ld = long double;
using ll = long long;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    ll mx = *max_element(all(a));
    ll ans = mx-1;
    for(ll dif = 1LL << 40; dif; dif /= 2) {
        ll cur = ans + dif;
        vl prov;
        prov.push_back(0);
        rep(i, 0, n){
            if(prov.back() + (prov.back() > 0) + a[i] > cur){
                prov.push_back(0);
            }
            prov.back() += a[i] + (prov.back() > 0);
        }
        if(sz(prov) > k) ans = cur;
    }
    ans++;
    cout << ans << "\n";
    return 0;
}
